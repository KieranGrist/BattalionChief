// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseEquipmentActor.h"

// Sets default values
ABaseEquipmentActor::ABaseEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEquipmentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEquipmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

