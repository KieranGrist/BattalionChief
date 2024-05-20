// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/FirstAidKit.h"

// Sets default values
AFirstAidKit::AFirstAidKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFirstAidKit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstAidKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstAidKit::UseEquipment()
{
	return Super::UseEquipment();
}

bool AFirstAidKit::CanUseEquipment() const
{
	return Super::CanUseEquipment();
}

float AFirstAidKit::ScoreEquipment() const
{
	return Super::ScoreEquipment();
}