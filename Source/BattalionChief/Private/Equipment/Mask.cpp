// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Mask.h"

// Sets default values
AMask::AMask()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMask::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMask::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMask::UseEquipment()
{
	return Super::UseEquipment();
}

bool AMask::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float AMask::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}