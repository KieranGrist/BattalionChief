// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseCharacter.h"
#include "Engine/LocalPlayer.h"
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

	HelmetAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HelmetAttachPoint"));
	HelmetAttachPoint->SetupAttachment(RootComponent);

	FaceAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("FaceAttachPoint"));
	FaceAttachPoint->SetupAttachment(RootComponent);

	TorsoAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TorsoAttachPoint"));
	TorsoAttachPoint->SetupAttachment(RootComponent);

	LegsAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LegsAttachPoint"));
	LegsAttachPoint->SetupAttachment(RootComponent);

	LeftHandAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandAttachPoint"));
	LeftHandAttachPoint->SetupAttachment(RootComponent);

	RightHandAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandAttachPoint"));
	RightHandAttachPoint->SetupAttachment(RootComponent);
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
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABaseCharacter::Interact(const FInputActionValue& Value)
{
	FVector start_location = GetActorLocation(); // Get the character's current location
	FVector end_location = start_location + (GetActorForwardVector() * InteractionRange); // Calculate the end location based on the character's forward vector and max trace distance

	FHitResult hit_result;
	FCollisionQueryParams collision_params;
	collision_params.AddIgnoredActor(this); // Ignore the character itself during the line trace
	collision_params.AddIgnoredActor(Helmet); // Ignore held equipment
	collision_params.AddIgnoredActor(Face); // Ignore held equipment
	collision_params.AddIgnoredActor(Torso);  // Ignore held equipment
	collision_params.AddIgnoredActor(Legs);  // Ignore held equipment
	collision_params.AddIgnoredActor(LeftHand);  // Ignore held equipment
	collision_params.AddIgnoredActor(RightHand);  // Ignore held equipment

	// Perform the line trace
	if (GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, ECC_Visibility, collision_params))
	{
		// Check if the hit actor is valid
		ABaseObjectActor* hit_actor = Cast<ABaseObjectActor>(hit_result.GetActor());
		if (!hit_actor)
			return;
		// Handle the hit actor, such as storing its reference or performing some action
		// For example:
		float DistanceToHitActor = FVector::Distance(start_location, hit_result.ImpactPoint);
		UE_LOG(LogTemp, Warning, TEXT("Nearest object hit: %s, Distance: %f"), *hit_actor->GetName(), DistanceToHitActor);

		// Draw a debug line to visualize the line trace
		DrawDebugLine(GetWorld(), start_location, hit_result.ImpactPoint, FColor::Green, false, 1.0f);


		ABaseEquipmentActor* hit_equipment = Cast<ABaseEquipmentActor>(hit_actor);
		if (hit_equipment)
		{
			EquipEquipment(hit_equipment, hit_equipment->GetCharacterEquipmentSlot());
		}
	}
}

void ABaseCharacter::PrimaryAction(const FInputActionValue& Value)
{

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

void ABaseCharacter::AttachEquipment(ABaseEquipmentActor* Equipment, USceneComponent* AttachPoint)
{
	if (Equipment && AttachPoint)
	{
		// Attach the equipment actor to the specified attach point
		Equipment->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
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
