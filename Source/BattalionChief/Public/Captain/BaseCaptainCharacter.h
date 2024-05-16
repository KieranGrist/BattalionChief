#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseCaptainCharacter.generated.h"

UCLASS()
class BATTALIONCHIEF_API ABaseCaptainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseCaptainCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;
};
