// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firefighter/Actions/BaseActionComponent.h"
#include "BreakWindowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTALIONCHIEF_API UBreakWindowComponent : public UBaseActionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBreakWindowComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Executes the action
	virtual void ExecuteAction() PURE_VIRTUAL(ABaseObjectActor::ExecuteAction, );

	// Checks if the action can be done
	virtual bool CanActionBeCompleted() const PURE_VIRTUAL(ABaseObjectActor::CanActionBeCompleted, return false;);
};
