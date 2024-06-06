// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/EngineTypes.h"
#include "Equipment/BaseEquipmentActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Logging/LogMacros.h"
#include "BaseCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBaseCharacter, Log, All);

UCLASS(config = Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Interact with world objects */
	void Interact(const FInputActionValue& Value);

	/** Use a tool you are holding */
	void PrimaryAction(const FInputActionValue& Value);
	
	void SecondaryAction(const FInputActionValue& Value);

	void EquipEquipment(ABaseEquipmentActor* InEquipment, ECharacterEquipmentSlotType InSlot);
	
	void UnequipEquipment(ECharacterEquipmentSlotType InSlot);
	
	void SetupEquipmentSockets();

	void SpawnAndAttach();

	// This will handle a player possessing a character;
	virtual void PlayerPossessCharacter();

	// This will handle cleanup
	virtual void PlayerUnPossessCharacter();

	// Overriden in the BP to create the correct UI 
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
	void CreateUI();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	FBaseCharacterEquipmentSlot HelmetCharacterEquipmentSlot  = FBaseCharacterEquipmentSlot(ECharacterEquipmentSlotType::Helmet, FName("HelmetSocket"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	FBaseCharacterEquipmentSlot FaceCharacterEquipmentSlot  = FBaseCharacterEquipmentSlot(ECharacterEquipmentSlotType::Face, FName("FaceSocket"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	FPocketEquipment TorsoCharacterEquipmentSlot  = FPocketEquipment(ECharacterEquipmentSlotType::Face, FName("TorsoSocket"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	FPocketEquipment LegsCharacterEquipmentSlot  = FPocketEquipment(ECharacterEquipmentSlotType::Face, FName("LegsSocket"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	FBaseCharacterEquipmentSlot LeftHandCharacterEquipmentSlot  = FBaseCharacterEquipmentSlot(ECharacterEquipmentSlotType::Face, FName("LeftHandSocket"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	FBaseCharacterEquipmentSlot RightHandCharacterEquipmentSlot  = FBaseCharacterEquipmentSlot(ECharacterEquipmentSlotType::Face, FName("RightHandSocket"));

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* JumpInputAction;

	/** Interact with world objects */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InteractInputAction;

	/**  Primary Action of the equipment */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* PrimaryInputAction;

	/** Secondary action of equipment */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SecondaryInputAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* MoveInputAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* LookInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseCharacter)
	TSubclassOf<APlayerController> CreatedPlayerControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseCharacter)
	TSubclassOf<AAIController> CreatedAIControllerClass;

	UPROPERTY(EditAnywhere,  Category = Interaction)
	float InteractionRange = 150;

	UPROPERTY(EditAnywhere, Category = Interaction)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = Interaction)
	FVector EndLocation;

	UPROPERTY(EditAnywhere, Category = Interaction)
	FVector HalfSize;

	UPROPERTY(EditAnywhere, Category = Interaction)
	FRotator Orientation;

	UPROPERTY(EditAnywhere, Category = Interaction)
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	bool TraceComplex;

	UPROPERTY(EditAnywhere, Category = Interaction)
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere, Category = Interaction)
	FHitResult HitResult;

	UPROPERTY(EditAnywhere, Category = Interaction)
	bool IgnoreSelf;

	UPROPERTY(EditAnywhere, Category = Interaction)
	FLinearColor TraceColor;

	UPROPERTY(EditAnywhere, Category = Interaction)
	FLinearColor TraceHitColor;

	UPROPERTY(EditAnywhere, Category = Interaction)
	float DrawTime = 10;
};
