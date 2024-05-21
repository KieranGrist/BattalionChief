// Fill out your copyright notice in the Description page of Project Settings.
#include "ExtinguisherTypes/BaseExtinguisherTypeComponent.h"

// Sets default values for this component's properties
UBaseExtinguisherTypeComponent::UBaseExtinguisherTypeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Default extinguishing power
	ExtinguishPower = 10.0f;
}

// Called when the game starts
void UBaseExtinguisherTypeComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UBaseExtinguisherTypeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Get the extinguishing power of this component
float UBaseExtinguisherTypeComponent::GetExtinguishPower() const
{
	return ExtinguishPower;
}

// Set the extinguishing power of this component
void UBaseExtinguisherTypeComponent::SetExtinguishPower(float NewPower)
{
	ExtinguishPower = NewPower;
}

float UBaseExtinguisherTypeComponent::GetObjectDamage() const
{
	return ObjectDamage;
}

void UBaseExtinguisherTypeComponent::SetObjectDamage(float InObjectDamage)
{
	ObjectDamage = InObjectDamage;
}
