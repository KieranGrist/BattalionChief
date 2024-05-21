// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Ladder.h"

// Sets default values
ALadder::ALadder() : ABaseEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadder::UseEquipment()
{
	return Super::UseEquipment();
}

bool ALadder::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float ALadder::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}