// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/BaseFirefighterPawn.h"

// Sets default values
ABaseFireFighterPawn::ABaseFireFighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseFireFighterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseFireFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseFireFighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

