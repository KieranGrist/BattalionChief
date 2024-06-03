// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fires/BaseFireComponent.h"
#include "ClassBFire.generated.h"

/**
 * Flammable liquids like gasoline, oil, paint, and grease (but not cooking oils and fats).
 */
UCLASS()
class BATTALIONCHIEF_API UClassBFire : public UBaseFireComponent
{
	GENERATED_BODY()

public:
	UClassBFire();
};
