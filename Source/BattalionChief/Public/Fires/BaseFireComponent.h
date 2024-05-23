// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "ExtinguisherTypes/BaseExtinguisherTypeComponent.h"
#include "Logging/LogMacros.h"
#include "BaseFireComponent.generated.h"


class ABaseObjectActor;

UCLASS(BlueprintType, Blueprintable)
class BATTALIONCHIEF_API UBaseFireComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UBaseFireComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void CalculateHeat();
	
	virtual void CalculateIntensity();

	virtual void CalculateSpreadRadius();

	virtual void CalculateSpreadRate();

	virtual void CalculateHealth();

	// Function to spread the fire
	virtual void Spread();

	// Function to simulate burning
	virtual void Burn();

	// Function called when the fire is hit by an object containing extinguisher info
	virtual void Extinguish(UBaseExtinguisherTypeComponent* InBaseExtinguisherTypeComponent);

	// Function to calculate damage to burning objects
	virtual float CalculateDamage();

	// ApplyDamage to burning objects
	virtual void ApplyDamage();

	// Function to update visual and audio effects
	void UpdateEffects();

	// The object that is burning
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	ABaseObjectActor* BurningObject;
protected:
	// Extinguishers that deal damage and stop this fire, float represents extinguishing percentage
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	TMap<TSubclassOf<UBaseExtinguisherTypeComponent>, float> HelpfulExtinguisherTypesMap;

	// Extinguishers that spread the fire 
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	TMap<TSubclassOf<UBaseExtinguisherTypeComponent>, float> HinderingExtinguisherTypesMap;

	// The heat generated by the fire
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	float Heat = 100.0f; 

	// The intensity of the fire
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	float Intensity = 1.0f;

	// The radius within which the fire can spread
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	float SpreadRadius = 100.0f; 

	// The rate at which the fire spreads
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	float SpreadRate = 1.0f; 

	// The current health of the fire (used to determine if it should be extinguished)
	UPROPERTY(EditAnywhere, Category = "Fire Properties")
	float Health = 100.0f; 
};