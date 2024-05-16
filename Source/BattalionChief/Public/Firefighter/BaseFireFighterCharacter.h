// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseFireFighterCharacter.generated.h"

UCLASS()
class BATTALIONCHIEF_API ABaseFireFighterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABaseFireFighterCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;
};
