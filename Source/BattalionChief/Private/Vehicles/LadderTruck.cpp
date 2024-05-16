// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/LadderTruck.h"

// Sets default values
ALadderTruck::ALadderTruck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALadderTruck::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALadderTruck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

