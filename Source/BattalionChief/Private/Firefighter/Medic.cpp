// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/Medic.h"

// Sets default values
AMedic::AMedic()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMedic::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMedic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMedic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
