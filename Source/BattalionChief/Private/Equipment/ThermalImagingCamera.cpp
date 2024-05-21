// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/ThermalImagingCamera.h"

// Sets default values
AThermalImagingCamera::AThermalImagingCamera() : ABaseEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThermalImagingCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThermalImagingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThermalImagingCamera::UseEquipment()
{
	return Super::UseEquipment();
}

bool AThermalImagingCamera::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float AThermalImagingCamera::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}