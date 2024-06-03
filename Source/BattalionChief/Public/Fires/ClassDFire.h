// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fires/BaseFireComponent.h"
#include "ClassDFire.generated.h"

/**
 * Combustible metals like magnesium, titanium, aluminum, and potassium.
 */
UCLASS()
class BATTALIONCHIEF_API UClassDFire : public UBaseFireComponent
{
	GENERATED_BODY()

public:
	UClassDFire();
};
