// Fill out your copyright notice in the Description page of Project Settings.
#include "Fires/BaseFireComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Objects/BaseObjectActor.h"
#include "Engine/World.h"
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
}

void UBaseFireComponent::CalculateIntensity()
{
}

void UBaseFireComponent::CalculateSpreadRadius()
{
}

void UBaseFireComponent::CalculateSpreadRate()
{
}

void UBaseFireComponent::CalculateHealth()
{
}

// Function to spread the fire
void UBaseFireComponent::Spread()
{
    // Implement fire spreading logic
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
}
