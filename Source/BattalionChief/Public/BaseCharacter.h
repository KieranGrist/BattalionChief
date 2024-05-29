// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
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

	// This will handle a player possessing a character;
	virtual void PlayerPossessCharacter();

	// This will handle cleanup
	virtual void PlayerUnPossessCharacter();

	// Overriden in the BP to create the correct UI 
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
	void CreateUI();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	ABaseEquipmentActor* Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	ABaseEquipmentActor* FaceWear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	ABaseEquipmentActor* Torso;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	ABaseEquipmentActor* Legs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	ABaseEquipmentActor* LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	ABaseEquipmentActor* RightHand;

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
};


