// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/Actions/SprayComponent.h"

// Sets default values for this component's properties
USprayComponent::USprayComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USprayComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USprayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USprayComponent::ExecuteAction()
{
	return Super::ExecuteAction();
}

bool USprayComponent::CanActionBeCompleted() const
{
	return Super::CanActionBeCompleted();
}

float USprayComponent::ScoreAction()
{
	return Super::ScoreAction();
}
