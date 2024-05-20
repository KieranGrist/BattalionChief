// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firefighter/Actions/BaseActionComponent.h"
#include "UseToolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTALIONCHIEF_API UUseToolComponent : public UBaseActionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUseToolComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Executes the action
	virtual void ExecuteAction() PURE_VIRTUAL(ABaseObjectActor::ExecuteAction, );

	// Checks if the action can be done
	virtual bool CanActionBeCompleted() const PURE_VIRTUAL(ABaseObjectActor::CanActionBeCompleted, return false;);
};
