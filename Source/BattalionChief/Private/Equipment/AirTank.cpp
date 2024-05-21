// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/AirTank.h"

// Sets default values
AAirTank::AAirTank() : ABaseEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAirTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAirTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAirTank::UseEquipment()
{
	return Super::UseEquipment();
}

bool AAirTank::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float AAirTank::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}

