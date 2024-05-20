// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Chainsaw.h"

// Sets default values
AChainsaw::AChainsaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChainsaw::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChainsaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChainsaw::UseEquipment()
{
	return Super::UseEquipment();
}

bool AChainsaw::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float AChainsaw::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}