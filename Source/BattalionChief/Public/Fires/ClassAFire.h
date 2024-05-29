// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fires/BaseFireComponent.h"
#include "ClassAFire.generated.h"

/**
 * Ordinary combustibles such as wood, paper, cloth, trash, and plastics.
 */
UCLASS()
class BATTALIONCHIEF_API UClassAFire : public UBaseFireComponent
{
	GENERATED_BODY()

public:
	UClassAFire();
};
