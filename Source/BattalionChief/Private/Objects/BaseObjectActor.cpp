// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/BaseObjectActor.h"

// Sets default values
ABaseObjectActor::ABaseObjectActor()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = false;

	// Set default health
	Health = 100.0f;
}

// Called when the game starts or when spawned
void ABaseObjectActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseObjectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function to apply damage to this object
void ABaseObjectActor::ApplyDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		OnObjectDestroyed_BP();
		OnObjectDestroyed.Broadcast(this);
	}
}

void ABaseObjectActor::Ignite(ABaseFireActor* InFire)
{

}

void ABaseObjectActor::UpdateSelfIgnitionChance()
{
}
