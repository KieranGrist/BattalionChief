// Fill out your copyright notice in the Description page of Project Settings.
#include "Fires/BaseFireComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Objects/BaseObjectActor.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "PhysicsEngine/BodySetup.h"
#include "DrawDebugHelpers.h"

// Sets default values
UBaseFireComponent::UBaseFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UBaseFireComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Burn();
	Spread();
}


void UBaseFireComponent::CalculateHeat()
{
	Heat = 100.0f;
	Intensity = 1.0f;
	SpreadRadius = 100.0f;
	SpreadChance = 1.0f;
	Health = 100.0f;
}

void UBaseFireComponent::CalculateIntensity()
{
}

void UBaseFireComponent::CalculateSpreadRadius()
{
	if (!BurningObject)
		return;
	UStaticMeshComponent* mesh = BurningObject->GetObjectMesh();

	if (!mesh)
		return;

	ScaledBoxExtent = FVector::ZeroVector;

	CollisionBoxFullExtent = FVector::ZeroVector;

	CollisionBoxHalfExtent = FVector::ZeroVector;

	SpreadRadius = 100.0f;


	UBodySetup* body_setup = mesh->GetBodySetup();
	// Check if the mesh has convex collision elements
	if (body_setup && body_setup->AggGeom.ConvexElems.Num() > 0)
	{
		// Calculate the bounding box of all convex elements
		CollisionBox = FBox(ForceInit);
		for (const FKConvexElem& convex_elem : body_setup->AggGeom.ConvexElems)
		{
			CollisionBox += convex_elem.ElemBox.GetExtent();
		}

		CollisionBoxHalfExtent = CollisionBox.GetExtent();
		CollisionBoxFullExtent = CollisionBoxHalfExtent * 2.0f;
		ScaledBoxExtent = CollisionBoxFullExtent * mesh->GetComponentScale();
	}
	else
	{
		// Use the bounding box of the static mesh
		CollisionBox = mesh->GetStaticMesh()->GetBoundingBox();

		// Calculate the CollisionBoxFullExtent
		CollisionBoxHalfExtent = Bounds.BoxExtent;
		CollisionBoxFullExtent = CollisionBoxHalfExtent * 2;
		ScaledBoxExtent = CollisionBoxFullExtent * mesh->GetComponentScale();
	}

	SpreadRadius = ScaledBoxExtent.GetMax() + FireSpreadRadius;
}

void UBaseFireComponent::CalculateSpreadChance()
{
}

void UBaseFireComponent::CalculateHealth()
{

}

// Function to spread the fire
void UBaseFireComponent::Spread()
{
	if (!BurningObject)
		return;
	CalculateSpreadRadius();
	// Perform a box trace around the owner actor to find neighboring objects within the spread radius
	TArray<FHitResult> hit_results;
	FVector start_location = BurningObject->GetActorLocation();
	FCollisionShape collision_shape = FCollisionShape::MakeSphere(SpreadRadius);
	FQuat rotation = FQuat::Identity;
	FCollisionQueryParams collision_params;
	collision_params.AddIgnoredActor(BurningObject); // Ignore the owner actor itself

	GetWorld()->SweepMultiByChannel(hit_results, start_location, start_location, rotation, ECC_WorldDynamic, collision_shape, collision_params);

	for (const FHitResult& hit_result : hit_results)
	{
		ABaseObjectActor* hit_actor = Cast<ABaseObjectActor>(hit_result.GetActor());
		if (!hit_actor || hit_actor == BurningObject)
			continue;

		float random_value = FMath::FRandRange(0.0f, 100.0f); // Generate a random float between 0 and 1
		//UE_LOG(LogFire, Log,
		//	TEXT("ABaseFireComponent::Spread    Random Value: %f <= Spread chancce: %f"),
		//	random_value, SpreadChance);
		if (random_value > SpreadChance)
			continue;
		//UE_LOG(LogFire, Log, TEXT("ABaseFireComponent::Spread    Spreading to %s"), *hit_actor->GetActorLabel());
		hit_actor->IgniteFire(this);
	}
	// Debug visualization of the spread radius (optional)
	DrawDebugSphere(GetWorld(), start_location, SpreadRadius, 12, FColor::Red, false, 1.0f);
}


// Function to simulate burning
void UBaseFireComponent::Burn()
{
	// Implement burning logic, like reducing the health of the burning object
	ApplyDamage();
}

// Function called when the fire is hit by an object containing extinguisher info
void UBaseFireComponent::Extinguish(UBaseExtinguisherTypeComponent* InBaseExtinguisherTypeComponent)
{
	float* efficiency = HelpfulExtinguisherTypesMap.Find(InBaseExtinguisherTypeComponent->GetClass());
	if (efficiency)
	{
		float starting_health = Health;
		Health -= InBaseExtinguisherTypeComponent->GetExtinguishPower() * *efficiency;
		float ending_health = Health;
		float health_loss = starting_health - ending_health;

		UE_LOG(LogFire, Log,
			TEXT("ABaseFireComponent::Extinguish    InBaseExtinguisherTypeComponentClass: %s is HELPFUL, efficiency: %f, GetExtinguishPower: %f, Starting Health: %f, Ending Health: %f, Health Loss: %f"),
			*InBaseExtinguisherTypeComponent->GetClass()->GetName(), *efficiency, InBaseExtinguisherTypeComponent->GetExtinguishPower(), starting_health, ending_health, health_loss);

		if (Health <= 0)
		{
			BurningObject->ExtinguishFire();
		}
	}

	efficiency = HinderingExtinguisherTypesMap.Find(InBaseExtinguisherTypeComponent->GetClass());
	if (efficiency)
	{
		float starting_health = Health;
		Health += InBaseExtinguisherTypeComponent->GetExtinguishPower() * *efficiency;
		float ending_health = Health;
		float health_gain = ending_health - starting_health;

		UE_LOG(LogFire, Log,
			TEXT("ABaseFireComponent::Extinguish    InBaseExtinguisherTypeComponentClass: %s is HINDERING, efficiency: %f, GetExtinguishPower: %f, Starting Health: %f, Ending Health: %f, Health Gain: %f"),
			*InBaseExtinguisherTypeComponent->GetClass()->GetName(), *efficiency, InBaseExtinguisherTypeComponent->GetExtinguishPower(), starting_health, ending_health, health_gain);

		Spread();
	}
}

// Function to calculate damage to burning objects
float UBaseFireComponent::CalculateDamage()
{
	UE_LOG(LogFire, Log,
		TEXT("ABaseFireComponent::CalculateDamage    Heat: %f * Intensity: %f * DeltaSeconds: %f = %f"),
		Heat, Intensity, GetWorld()->GetDeltaSeconds(), Heat * Intensity * GetWorld()->GetDeltaSeconds());
	return Heat * Intensity * GetWorld()->GetDeltaSeconds();
}

// Apply damage to burning objects
void UBaseFireComponent::ApplyDamage()
{
	if (BurningObject)
	{
		BurningObject->ApplyDamage(CalculateDamage());
	}
}

TSubclassOf<UBaseFireComponent> UBaseFireComponent::GetFireType() const
{
	return GetClass();
}

ABaseObjectActor* UBaseFireComponent::GetBurningObject() const
{
	return BurningObject;
}

void UBaseFireComponent::SetBurningObject(ABaseObjectActor* InBurningObject)
{
	BurningObject = InBurningObject;
	CalculateSpreadRadius();
}
