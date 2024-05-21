// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Radio.h"

// Sets default values
ARadio::ARadio() : ABaseEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARadio::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARadio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARadio::UseEquipment()
{
	return Super::UseEquipment();
}

bool ARadio::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float ARadio::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}