// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/BaseObjectActor.h"

// Sets default values
ABaseObjectActor::ABaseObjectActor()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = false;

	// Set default health
	Health = 100.0f;


	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HitBox->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	HitBox->SetGenerateOverlapEvents(true);
	HitBox->SetNotifyRigidBodyCollision(true);
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

void ABaseObjectActor::Ignite(UBaseFireComponent* InFire)
{

}

void ABaseObjectActor::CalculateTemperature()
{
}

void ABaseObjectActor::CalculateFlambility()
{
}

void ABaseObjectActor::CalculateSelfIgnitionChance()
{
}

void ABaseObjectActor::SelfIgnite()
{
	// Spawn the projectile
	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	UBaseFireComponent* spawned_fire = GetWorld()->SpawnActor<UBaseFireComponent>(FireType, GetActorLocation(), FRotator::ZeroRotator, spawn_params);

		
}

