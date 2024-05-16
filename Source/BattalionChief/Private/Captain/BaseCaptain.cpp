// Fill out your copyright notice in the Description page of Project Settings.


#include "Captain/BaseCaptain.h"

// Sets default values
ABaseCaptain::ABaseCaptain()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCaptain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCaptain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCaptain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

