// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/BaseVehicleActor.h"
#include "Ambulance.generated.h"

UCLASS()
class BATTALIONCHIEF_API AAmbulance : public ABaseVehicleActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmbulance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
