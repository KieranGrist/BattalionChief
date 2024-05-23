// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/BaseObjectActor.h"
DEFINE_LOG_CATEGORY(LogFireExtinguisher);
DEFINE_LOG_CATEGORY(LogFire);

// Sets default values
ABaseObjectActor::ABaseObjectActor() : AActor()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = false;

	// Set default health
	Health = 100.0f;

	// Create the equipment mesh component and attach it to the root component
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMesh"));
	SetRootComponent(ObjectMesh);

	ObjectMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ObjectMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	ObjectMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ObjectMesh->SetGenerateOverlapEvents(true);
	ObjectMesh->SetNotifyRigidBodyCollision(true);

	// Initialize other components
	FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));
	FireParticles->SetupAttachment(ObjectMesh);

	FireSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound"));
	FireSound->SetupAttachment(ObjectMesh);
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

void ABaseObjectActor::IgniteFire(UBaseFireComponent* InFire)
{

}

void ABaseObjectActor::CalculateTemperature()
{
}

void ABaseObjectActor::CalculateFlammability()
{
}

void ABaseObjectActor::CalculateSelfIgnitionChance()
{
}

// Function to ignite fire
void ABaseObjectActor::SelfIgniteFire()
{
	if (FireComponent)
		return;
	FireComponent = NewObject<UBaseFireComponent>(this, FireType, TEXT("FireComponent"));

	if (FireComponent)
	{
		FireComponent->SetupAttachment(RootComponent);
		FireComponent->RegisterComponent();
		FireComponent->BurningObject = this;
		// Optionally set properties for the fire component here
		// For example, FireComponent->SetStaticMesh(SomeMesh);

		UE_LOG(LogFire, Log, TEXT("Fire ignited."));
	}
}

// Function to extinguish fire
void ABaseObjectActor::ExtinguishFire()
{
	if (!FireComponent)
		return;
	FireComponent->DestroyComponent();
	FireComponent = nullptr;

	UE_LOG(LogFire, Log, TEXT("Fire extinguished."));
}

bool ABaseObjectActor::IsOnFire()
{
	return IsValid(FireComponent);
}

void ABaseObjectActor::StartFireEffects()
{
	if (FireParticles)
	{
		FireParticles->ActivateSystem();
	}

	if (FireSound)
	{
		FireSound->Play();
	}
}

void ABaseObjectActor::StopFireEffects()
{
	if (FireParticles)
	{
		FireParticles->DeactivateSystem();
	}

	if (FireSound)
	{
		FireSound->Stop();
	}
}

