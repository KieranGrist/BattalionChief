// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chief.generated.h"

UCLASS()
class BATTALIONCHIEF_API AChief : public APawn
{
	GENERATED_BODY()

public:
	AChief();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;
};
