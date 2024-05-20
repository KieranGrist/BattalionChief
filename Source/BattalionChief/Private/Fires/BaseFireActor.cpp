// Fill out your copyright notice in the Description page of Project Settings.
#include "Fires/BaseFireActor.h"

// Sets default values
ABaseFireActor::ABaseFireActor()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Create a scene component and set it as the root component
	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);

	// Create the hitbox component
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);;
	//SetRootComponent(HitBox);

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

// Function called when the fire is hit by an object containing extinguisher info
void ABaseFireActor::Extinguish(UBaseExtinguisherTypeComponent* InBaseExtinguisherTypeComponent)
{
	float* value = HelpfulExtinguisherTypesMap.Find(InBaseExtinguisherTypeComponent->GetClass());
	if (value)
	{
		Health -= InBaseExtinguisherTypeComponent->GetExtinguishPower() * *value;
		if (Health <= 0)
		{
			Destroy();
		}
	}
	value = HinderingExtinguisherTypesMap.Find(InBaseExtinguisherTypeComponent->GetClass());
	if (value)
	{
		Health += InBaseExtinguisherTypeComponent->GetExtinguishPower() * *value;
		Spread();
	}
}

void ABaseFireActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor != this)
	{
		// Print a message to the screen
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap Begin with %s"), *OtherActor->GetName()));
		}

		// Additional overlap handling logic can go here
	}
}

void ABaseFireActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor && OtherActor != this)
	{
		// Print a message to the screen
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap End with %s"), *OtherActor->GetName()));
		}

		// Additional overlap handling logic can go here
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