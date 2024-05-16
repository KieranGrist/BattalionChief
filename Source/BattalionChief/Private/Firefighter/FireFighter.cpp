// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/FireFighter.h"

// Sets default values
AFireFighter::AFireFighter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFireFighter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

