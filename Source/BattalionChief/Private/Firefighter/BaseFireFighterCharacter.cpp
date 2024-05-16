// Fill out your copyright notice in the Description page of Project Settings.


#include "FireFighter/BaseFireFighterCharacter.h"

// Sets default values
ABaseFireFighterCharacter::ABaseFireFighterCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseFireFighterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseFireFighterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseFireFighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

