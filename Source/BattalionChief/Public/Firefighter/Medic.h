// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firefighter/BaseFirefighterPawn.h"
#include "Medic.generated.h"

UCLASS()
class BATTALIONCHIEF_API AMedic : public ABaseFireFighterPawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMedic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
