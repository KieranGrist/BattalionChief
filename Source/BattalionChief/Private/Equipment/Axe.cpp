// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Axe.h"

// Sets default values
AAxe::AAxe() : ABaseEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAxe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAxe::UseEquipment()
{
}

bool AAxe::CanUseEquipment() const
{
	return false;
}

float AAxe::ScoreEquipment() const
{
	return 0.0f;
}

