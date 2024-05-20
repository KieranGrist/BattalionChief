// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseObjectActor.h"
#include "Sofa.generated.h"

UCLASS()
class BATTALIONCHIEF_API ASofa : public ABaseObjectActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASofa();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
