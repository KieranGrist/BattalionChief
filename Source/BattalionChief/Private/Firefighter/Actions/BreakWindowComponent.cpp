// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/Actions/BreakWindowComponent.h"

// Sets default values for this component's properties
UBreakWindowComponent::UBreakWindowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBreakWindowComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBreakWindowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBreakWindowComponent::ExecuteAction()
{
	return Super::ExecuteAction();
}

bool UBreakWindowComponent::CanActionBeCompleted() const
{
	return Super::CanActionBeCompleted();
}

float UBreakWindowComponent::ScoreAction()
{
	return Super::ScoreAction();
}

