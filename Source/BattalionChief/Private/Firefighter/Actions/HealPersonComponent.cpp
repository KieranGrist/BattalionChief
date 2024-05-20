// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/Actions/HealPersonComponent.h"

// Sets default values for this component's properties
UHealPersonComponent::UHealPersonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealPersonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealPersonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealPersonComponent::ExecuteAction()
{
	return Super::ExecuteAction();
}

bool UHealPersonComponent::CanActionBeCompleted() const
{
	return Super::CanActionBeCompleted();
}

float UHealPersonComponent::ScoreAction()
{
	return Super::ScoreAction();
}
