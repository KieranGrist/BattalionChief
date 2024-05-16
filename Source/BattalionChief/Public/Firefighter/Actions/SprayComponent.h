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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
