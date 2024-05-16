// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firefighter/Actions/BaseActionComponent.h"
#include "HealPersonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTALIONCHIEF_API UHealPersonComponent : public UBaseActionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealPersonComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
