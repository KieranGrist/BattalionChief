// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseExtinguisherTypeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTALIONCHIEF_API UBaseExtinguisherTypeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseExtinguisherTypeComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get the extinguishing power of this component
	UFUNCTION(BlueprintCallable, Category = "Extinguishing")
	float GetExtinguishPower() const;

	// Set the extinguishing power of this component
	UFUNCTION(BlueprintCallable, Category = "Extinguishing")
	void SetExtinguishPower(float InExtinguishPower);

	// Get the extinguishing power of this component
	UFUNCTION(BlueprintCallable, Category = "Extinguishing")
	float GetObjectDamage() const;

	// Set the extinguishing power of this component
	UFUNCTION(BlueprintCallable, Category = "Extinguishing")
	void SetObjectDamage(float InObjectDamage);

protected:
	// The extinguishing power of this component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extinguishing")
	float ExtinguishPower;
	
	// Certain Extinguishers can cause damage to objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extinguishing")
	float ObjectDamage;
};