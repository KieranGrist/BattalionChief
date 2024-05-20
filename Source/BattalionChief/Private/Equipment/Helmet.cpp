// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Helmet.h"

// Sets default values
AHelmet::AHelmet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHelmet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHelmet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHelmet::UseEquipment()
{
	return Super::UseEquipment();
}

bool AHelmet::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float AHelmet::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}