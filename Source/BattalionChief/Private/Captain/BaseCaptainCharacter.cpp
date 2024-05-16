// Fill out your copyright notice in the Description page of Project Settings.


#include "Captain/BaseCaptainCharacter.h"

// Sets default values
ABaseCaptainCharacter::ABaseCaptainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCaptainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCaptainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCaptainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

