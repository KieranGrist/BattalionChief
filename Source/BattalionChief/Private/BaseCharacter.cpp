// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogBaseCharacter);

//////////////////////////////////////////////////////////////////////////
// ABaseCharacter

ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ABaseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);


		/** Interact with world objects */
		EnhancedInputComponent->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Interact);

		/** Use a tool you are holding */
		EnhancedInputComponent->BindAction(PrimaryInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::PrimaryAction);

		/** Use a tool you are holding */
		EnhancedInputComponent->BindAction(SecondaryInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::SecondaryAction);

		// Moving
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
	}
	else
	{
		UE_LOG(LogBaseCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D look_axis_vector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(look_axis_vector.X);
		AddControllerPitchInput(look_axis_vector.Y);
	}
}

void ABaseCharacter::Interact(const FInputActionValue& Value)
{
	StartLocation = GetActorLocation(); // Get the character's current location
	Orientation = GetActorRotation();

	// Calculate the end location based on the forward vector and interaction range
	EndLocation = StartLocation + (Orientation.Vector() * InteractionRange);

	ActorsToIgnore = 
	{
		this,
		Helmet,
		Face,
		Torso,
		Legs,
		LeftHand,
		RightHand
	};
	UKismetSystemLibrary::BoxTraceSingle(this, StartLocation, EndLocation, HalfSize, Orientation, TraceChannel, TraceComplex, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, IgnoreSelf, TraceColor, TraceHitColor, DrawTime);

	// Perform the line trace
	if (!HitResult.GetActor())
		return;
	// Check if the hit actor is valid
	ABaseObjectActor* hit_actor = Cast<ABaseObjectActor>(HitResult.GetActor());
	if (!hit_actor)
		return;

	float distance_to_hit_actor = FVector::Distance(StartLocation, HitResult.ImpactPoint);
	UE_LOG(LogBaseCharacter, Log, TEXT("Nearest object hit: %s, Distance: %f"), *hit_actor->GetName(), distance_to_hit_actor);

	ABaseEquipmentActor* hit_equipment = Cast<ABaseEquipmentActor>(hit_actor);
	if (!hit_equipment)
		return;

	EquipEquipment(hit_equipment, hit_equipment->GetCharacterEquipmentSlot());
}

void ABaseCharacter::PrimaryAction(const FInputActionValue& Value)
{
	if (RightHand)
	{
		RightHand->UseEquipment();
		return;
	}

	if (LeftHand)
	{
		LeftHand->UseEquipment();
		return;
	}
}

void ABaseCharacter::SecondaryAction(const FInputActionValue& Value)
{

}

void ABaseCharacter::EquipEquipment(ABaseEquipmentActor* InEquipment, ECharacterEquipmentSlot InSlot)
{
	switch (InSlot)
	{
	case ECharacterEquipmentSlot::Helmet:
		Helmet = InEquipment;
		AttachEquipment(Helmet, HelmetAttachPoint);
		break;
	case ECharacterEquipmentSlot::Face:
		Face = InEquipment;
		AttachEquipment(Face, FaceAttachPoint);
		break;
	case ECharacterEquipmentSlot::Torso:
		Torso = InEquipment;
		AttachEquipment(Torso, TorsoAttachPoint);
		break;
	case ECharacterEquipmentSlot::Legs:
		Legs = InEquipment;
		AttachEquipment(Legs, LegsAttachPoint);
		break;
	case ECharacterEquipmentSlot::BothHands:
		RightHand = InEquipment;
		LeftHand = InEquipment;
		AttachEquipment(RightHand, RightHandAttachPoint);
		break;
	case ECharacterEquipmentSlot::LeftHand:
		LeftHand = InEquipment;
		AttachEquipment(LeftHand, LeftHandAttachPoint);
		break;
	case ECharacterEquipmentSlot::RightHand:
		RightHand = InEquipment;
		AttachEquipment(RightHand, RightHandAttachPoint);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot selected for equipment"));
		break;
	}
}

void ABaseCharacter::AttachEquipment(ABaseEquipmentActor* InEquipment, const FName& InSocketName)
{
	USkeletalMeshComponent* character_mesh = GetMesh();
	if (!InEquipment || !character_mesh)
		return;
	
	const USkeletalMeshSocket* socket = character_mesh->GetSocketByName(InSocketName);
	InEquipment->GetObjectMesh()->SetSimulatePhysics(false);
	InEquipment->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InSocketName);
	InEquipment->SetActorRelativeLocation(InEquipment->GetSlotRelativeGap());
	InEquipment->SetActorRelativeRotation(InEquipment->GetSlotRelativeRotation());
}

void ABaseCharacter::DeAttachEquipment(ECharacterEquipmentSlot InSlot)
{
	switch (InSlot)
	{
	case ECharacterEquipmentSlot::Helmet:
		if (!Helmet)
			return;
		Helmet->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Helmet = nullptr;
		break;
	case ECharacterEquipmentSlot::Face:
		if (!Face)
			return;
		Face->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Face = nullptr;
		break;
	case ECharacterEquipmentSlot::Torso:
		if (!Torso)
			return;
		Torso->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Torso = nullptr;
		break;
	case ECharacterEquipmentSlot::Legs:
		if (!Legs)
			return;
		Legs->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Legs = nullptr;
		break;
	case ECharacterEquipmentSlot::BothHands:
		if (!RightHand)
			return;
		RightHand->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		RightHand = nullptr;
		LeftHand = nullptr;
		break;
	case ECharacterEquipmentSlot::LeftHand:
		if (!LeftHand)
			return;
		LeftHand->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		LeftHand = nullptr;
		break;
	case ECharacterEquipmentSlot::RightHand:
		if (!RightHand)
			return;
		RightHand->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		RightHand = nullptr;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot selected for equipment"));
		break;
	}
}

void ABaseCharacter::PlayerPossessCharacter()
{

}

void ABaseCharacter::PlayerUnPossessCharacter()
{

}
