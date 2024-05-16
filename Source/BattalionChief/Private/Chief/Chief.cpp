// Fill out your copyright notice in the Description page of Project Settings.


#include "Chief/Chief.h"

// Sets default values
AChief::AChief()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChief::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChief::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChief::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

