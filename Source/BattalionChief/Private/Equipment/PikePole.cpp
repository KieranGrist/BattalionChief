// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/PikePole.h"

// Sets default values
APikePole::APikePole() : ABaseEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APikePole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APikePole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APikePole::UseEquipment()
{
	return Super::UseEquipment();
}

bool APikePole::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float APikePole::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}