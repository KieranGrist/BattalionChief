// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/Actions/GrabObjectComponent.h"

// Sets default values for this component's properties
UGrabObjectComponent::UGrabObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrabObjectComponent::ExecuteAction()
{
	return Super::ExecuteAction();
}

bool UGrabObjectComponent::CanActionBeCompleted() const
{
	return Super::CanActionBeCompleted();
}

float UGrabObjectComponent::ScoreAction()
{
	return Super::ScoreAction();
}
