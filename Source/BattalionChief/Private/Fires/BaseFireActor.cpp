// Fill out your copyright notice in the Description page of Project Settings.
#include "Fires/BaseFireActor.h"

// Sets default values
ABaseFireActor::ABaseFireActor()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Create the hitbox component
	HitBox = CreateDefaultSubobject<UShapeComponent>(TEXT("HitBox"));
	// Set the hitbox as the root component
	RootComponent = HitBox;

	// Initialize other components
	FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));
	FireParticles->SetupAttachment(RootComponent);

	FireSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound"));
	FireSound->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseFireActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseFireActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Burn();
	Spread();
	UpdateEffects();
}

// Function to spread the fire
void ABaseFireActor::Spread()
{
	// Implement fire spreading logic
}

// Function to simulate burning
void ABaseFireActor::Burn()
{
	// Implement burning logic, like reducing the health of the burning object
	ApplyDamage();
}

// Function to extinguish the fire
void ABaseFireActor::Extinguish(UBaseExtinguisherTypeComponent* Extinguisher)
{
	if (HelpfulExtinguisherTypes.Contains(Extinguisher->GetClass()))
	{
		Health -= Extinguisher->GetExtinguishPower();
		if (Health <= 0)
		{
			Destroy();
		}
	}
	else if (HinderingExtinguisherTypes.Contains(Extinguisher->GetClass()))
	{
		// Implement logic if the extinguisher hinders fire suppression
	}
}

// Function to calculate damage to burning objects
float ABaseFireActor::CalculateDamage()
{
	return Heat * Intensity * GetWorld()->GetDeltaSeconds();
}

// Apply damage to burning objects
void ABaseFireActor::ApplyDamage()
{
	if (BurningObject)
	{
		BurningObject->ApplyDamage(CalculateDamage());
	}
}

// Function to update visual and audio effects
void ABaseFireActor::UpdateEffects()
{
	// Update particle and sound effects based on fire intensity, heat, and other properties
}