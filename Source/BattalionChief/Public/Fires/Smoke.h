// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fires/BaseFireComponent.h"
#include "Smoke.generated.h"

UCLASS()
class BATTALIONCHIEF_API USmoke : public UBaseFireComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USmoke();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
