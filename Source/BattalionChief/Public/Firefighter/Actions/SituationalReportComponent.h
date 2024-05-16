// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firefighter/Actions/BaseActionComponent.h"
#include "SituationalReportComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTALIONCHIEF_API USituationalReportComponent : public UBaseActionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USituationalReportComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
