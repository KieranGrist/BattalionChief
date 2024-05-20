// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireFighter/BaseFireFighterCharacter.h"
#include "FireFighter.generated.h"

UCLASS()
class BATTALIONCHIEF_API AFireFighter : public ABaseFireFighterCharacter
{
	GENERATED_BODY()

public:
	AFireFighter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;
};
  