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
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	SetRootComponent(ObjectMesh);

	ObjectMesh->SetSimulatePhysics(true);
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

	SetupObjectMeshMaterial();
}

void ABaseObjectActor::SetupObjectMeshMaterial()
{
	if (!ObjectMesh)
		return;

	if (!ObjectsMaterialInterface)
		ObjectsMaterialInterface = ObjectMesh->GetMaterial(0);
	if (!ObjectsMaterialInterface)
		return;

	if (!ObjectsMaterialInstanceDynamic)
	{
		ObjectsMaterialInstanceDynamic = ObjectMesh->CreateDynamicMaterialInstance(0, ObjectsMaterialInterface); 
		ObjectMesh->SetMaterial(0, ObjectsMaterialInstanceDynamic);
	}

	for (const TPair<FName, FLinearColor>& vector_parameter_value_pair : VectorParameterValueMap)
	{
		ObjectsMaterialInstanceDynamic->SetVectorParameterValue(vector_parameter_value_pair.Key, vector_parameter_value_pair.Value);
	}
}

// Called when the game starts or when spawned
void ABaseObjectActor::BeginPlay()
{
	Super::BeginPlay();
	StopFireEffects();
	SetupObjectMeshMaterial();
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
		Destroy();
	}
}

void ABaseObjectActor::IgniteFire(UBaseFireComponent* InFire)
{
	if (Flammability == INDEX_NONE)
		return;
	if (FireComponent)
		return;

	FireComponent = NewObject<UBaseFireComponent>(this, InFire->GetFireType(), TEXT("FireComponent"));
	SetupFireComponent();
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

	FireComponent = NewObject<UBaseFireComponent>(this, CreatedFire, TEXT("FireComponent"));
	SetupFireComponent();
}

void ABaseObjectActor::SetupFireComponent()
{
	if (!FireComponent)
		return;

	FireComponent->SetupAttachment(RootComponent);
	FireComponent->RegisterComponent();
	FireComponent->SetBurningObject(this);
	// Optionally set properties for the fire component here
	// For example, FireComponent->SetStaticMesh(SomeMesh);
	StartFireEffects();
	UE_LOG(LogFire, Log, TEXT("Fire ignited. Type of %s"), *FireComponent->GetFireType()->GetName());
}



// Function to extinguish fire
void ABaseObjectActor::ExtinguishFire()
{
	if (!FireComponent)
		return;

	FireComponent->DestroyComponent();
	FireComponent = nullptr;

	UE_LOG(LogFire, Log, TEXT("Fire extinguished."));
	StopFireEffects();
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

// Static mesh component for equipment model
UFUNCTION(BlueprintCallable, Category = "Object")
UStaticMeshComponent* ABaseObjectActor::GetObjectMesh() const
{
	return ObjectMesh;
}

// Particle system for visual representation of fire
UFUNCTION(BlueprintCallable, Category = "Object")
UParticleSystemComponent* ABaseObjectActor::GetFireParticles() const
{
	return FireParticles;
}

// Audio component for fire sound effects
UFUNCTION(BlueprintCallable, Category = "Object")
UAudioComponent* ABaseObjectActor::GetFireSound() const
{
	return FireSound;
}

UFUNCTION(BlueprintCallable, Category = "Object")
UBaseFireComponent* ABaseObjectActor::GetFireComponent() const
{
	return FireComponent;
}

float ABaseObjectActor::GetHealth() const
{
	return Health;
}

float ABaseObjectActor::GetWeight() const
{
	return Weight;
}

float ABaseObjectActor::GetTemperature() const
{
	return Temperature;
}

float ABaseObjectActor::GetThermalConductivity() const
{
	return ThermalConductivity;
}

float ABaseObjectActor::GetSpecificHeatCapacity() const
{
	return SpecificHeatCapacity;
}

float ABaseObjectActor::GetInitialTemperature() const
{
	return InitialTemperature;
}

float ABaseObjectActor::GetFlammability() const
{
	return Flammability;
}

float ABaseObjectActor::GetSelfIgnitionChance() const
{
	return SelfIgnitionChance;
}
