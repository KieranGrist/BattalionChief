// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Nozzle.h"

// Sets default values
ANozzle::ANozzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANozzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANozzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

