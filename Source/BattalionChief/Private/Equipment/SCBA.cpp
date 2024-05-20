// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/SCBA.h"

// Sets default values
ASCBA::ASCBA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASCBA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCBA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCBA::UseEquipment()
{
	return Super::UseEquipment();
}

bool ASCBA::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float ASCBA::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}