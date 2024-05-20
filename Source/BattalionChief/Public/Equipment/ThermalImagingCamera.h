// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/BaseEquipmentActor.h"
#include "ThermalImagingCamera.generated.h"

UCLASS()
class BATTALIONCHIEF_API AThermalImagingCamera : public ABaseEquipmentActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThermalImagingCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Uses the equipment
	virtual void UseEquipment()  override;

	// Checks if the equipment can be used
	virtual bool CanUseEquipment() const override;

	// Returns a score for the equipment based on situation, used by captains
	virtual float ScoreEquipment() const  override;
};
