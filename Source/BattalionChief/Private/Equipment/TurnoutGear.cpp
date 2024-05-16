// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/TurnoutGear.h"

// Sets default values
ATurnoutGear::ATurnoutGear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurnoutGear::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurnoutGear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

