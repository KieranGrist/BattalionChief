// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtinguisherTypes/ExtinguisherProjectile.h"
#include "Objects/BaseObjectActor.h"

// Sets default values
AExtinguisherProjectile::AExtinguisherProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a scene component and set it as the root component
	//USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	//SetRootComponent(RootSceneComponent);

	// Create the static mesh component
	ExtinguisherProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtinguisherProjectileMesh"));
	SetRootComponent(ExtinguisherProjectileMesh);
	ExtinguisherProjectileMesh->SetSimulatePhysics(true);
	//ExtinguisherProjectileMesh->SetupAttachment(RootComponent);

	// Create the audio component
	ExtinguisherProjectileSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ExtinguisherProjectileSound"));
	ExtinguisherProjectileSound->SetupAttachment(ExtinguisherProjectileMesh);

	// Create the particle system component
	ExtinguisherProjectileParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExtinguisherProjectileParticles"));
	ExtinguisherProjectileParticles->SetupAttachment(ExtinguisherProjectileMesh);
}

// Called when the game starts or when spawned
void AExtinguisherProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExtinguisherProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime+=DeltaTime;

	// Check if the lifetime exceeds the maximum allowed time
	if (LifeTime > MaxLifeTime)
	{
		Destroy();
	}
}

void AExtinguisherProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor != this)
	{
		ABaseObjectActor* BaseObjectActor = Cast<ABaseObjectActor>(OtherActor);


		// Print a message to the screen
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap Begin with %s"), *OtherActor->GetName()));
		}

		// Additional overlap handling logic can go here
	}
}


void AExtinguisherProjectile::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor && OtherActor != this)
	{
		ABaseObjectActor* BaseObjectActor = Cast<ABaseObjectActor>(OtherActor);



		// Print a message to the screen
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap End with %s"), *OtherActor->GetName()));
		}

		// Additional overlap handling logic can go here
	}
}
