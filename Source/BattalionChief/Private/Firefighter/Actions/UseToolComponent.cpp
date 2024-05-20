// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/Actions/UseToolComponent.h"

// Sets default values for this component's properties
UUseToolComponent::UUseToolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUseToolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUseToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUseToolComponent::ExecuteAction()
{
	return Super::ExecuteAction();
}

bool UUseToolComponent::CanActionBeCompleted() const
{
	return Super::CanActionBeCompleted();
}

float UUseToolComponent::ScoreAction()
{
	return Super::ScoreAction();
}
