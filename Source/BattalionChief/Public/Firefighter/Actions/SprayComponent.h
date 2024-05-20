// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firefighter/Actions/BaseActionComponent.h"
#include "SprayComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTALIONCHIEF_API USprayComponent : public UBaseActionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprayComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Executes the action
	virtual void ExecuteAction() override;

	// Checks if the action can be done
	virtual bool CanActionBeCompleted() const override;

	// Returns an evaluated score of how good this action is, to be used by captains. 
	virtual float ScoreAction() override;
};
