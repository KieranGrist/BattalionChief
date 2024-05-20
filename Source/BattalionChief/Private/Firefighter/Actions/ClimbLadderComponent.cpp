// Fill out your copyright notice in the Description page of Project Settings.


#include "Firefighter/Actions/ClimbLadderComponent.h"

// Sets default values for this component's properties
UClimbLadderComponent::UClimbLadderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClimbLadderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClimbLadderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClimbLadderComponent::ExecuteAction()
{
	return Super::ExecuteAction();
}

bool UClimbLadderComponent::CanActionBeCompleted() const
{
	return Super::CanActionBeCompleted();
}

float UClimbLadderComponent::ScoreAction()
{
	return Super::ScoreAction();
}
