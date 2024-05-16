// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattalionChiefGameMode.h"
#include "UObject/ConstructorHelpers.h"

ABattalionChiefGameMode::ABattalionChiefGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
