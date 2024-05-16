// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/BaseFirefighterPawn.h"

// Sets default values
ABaseFirefighterPawn::ABaseFirefighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseFirefighterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseFirefighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseFirefighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

