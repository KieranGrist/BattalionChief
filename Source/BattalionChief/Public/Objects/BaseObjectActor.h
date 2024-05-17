#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObjectActor.generated.h"

// Event dispatcher to notify when the object is destroyed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDestroyedSignature, ABaseObjectActor*, DestroyedObject);

UCLASS()
class BATTALIONCHIEF_API ABaseObjectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseObjectActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to apply damage to this object
	UFUNCTION(BlueprintCallable, Category = "Fire")
	void ApplyDamage(float InDamageAmount);

	// Function to ignite the object with a specific fire
	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Ignite(class ABaseFireActor* InFire);

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void UpdateSelfIgnitionChance();

	// Function called when the object is destroyed by fire
	UFUNCTION(BlueprintImplementableEvent, Category = "Fire")
	void OnObjectDestroyed_BP();

	// Event dispatcher to notify when the object is destroyed
	UPROPERTY(BlueprintAssignable, Category = "Fire")
	FOnObjectDestroyedSignature OnObjectDestroyed;
protected:
	// Health of the object
	UPROPERTY(EditAnywhere, Category = "Fire")
	float Health;

	// Weight of the object (affects fire spread and intensity)
	UPROPERTY(EditAnywhere, Category = "Fire")
	float Weight;

	// Objects Current Temperature
	UPROPERTY(EditAnywhere, Category = "Fire")
	float Temperature;
	
	// Flammability of the object (affects ignition probability and fire spread)
	UPROPERTY(EditAnywhere, Category = "Fire")
	float Flammability;

	// In the right conditions some objects can catch alight ig temp 
	UPROPERTY(EditAnywhere, Category = "Fire")
	float SelfIgnitionChance;

	// What Fire This Object Creates
	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<ABaseFireActor> FireType;
};
