#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fires/BaseFireComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "BaseObjectActor.generated.h"

// Event dispatcher to notify when the object is destroyed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDestroyedSignature, ABaseObjectActor*, DestroyedObject);

DECLARE_LOG_CATEGORY_EXTERN(LogFireExtinguisher, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogFire, Log, All);

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
	UFUNCTION(BlueprintCallable, Category = "Object")
	void ApplyDamage(float InDamageAmount);

	// Function to ignite the object with a specific fire
	UFUNCTION(BlueprintCallable, Category = "Object")
	void IgniteFire(UBaseFireComponent* InFire);

	UFUNCTION(BlueprintCallable, Category = "Object")
	void CalculateTemperature();

	UFUNCTION(BlueprintCallable, Category = "Object")
	void CalculateFlammability();

	UFUNCTION(BlueprintCallable, Category = "Object")
	void CalculateSelfIgnitionChance();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Object")
	void SelfIgniteFire();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Object")
	void ExtinguishFire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Object")
	void OnObjectDestroyed_BP();

	UFUNCTION(BlueprintCallable, Category = "Object")
	bool IsOnFire();

	UFUNCTION(BlueprintCallable, Category = "Object")
	virtual void StartFireEffects();
	
	UFUNCTION(BlueprintCallable, Category = "Object")
	virtual void StopFireEffects();

	// Event dispatcher to notify when the object is destroyed
	UPROPERTY(BlueprintAssignable, Category = "Object")
	FOnObjectDestroyedSignature OnObjectDestroyed;

	// Static mesh component for equipment model
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	UStaticMeshComponent* ObjectMesh;

	// Particle system for visual representation of fire
	UPROPERTY(EditAnywhere, Category = Fire)
	UParticleSystemComponent* FireParticles;

	// Audio component for fire sound effects
	UPROPERTY(EditAnywhere, Category = Fire)
	UAudioComponent* FireSound;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	UBaseFireComponent* FireComponent;

	// Health of the object
	UPROPERTY(EditAnywhere, Category = "Object")
	float Health = -1.0f;

	// Weight of the object (affects fire spread and intensity)
	UPROPERTY(EditAnywhere, Category = "Object")
	float Weight = -1.0f;

	// Objects Current Temperature
	UPROPERTY(EditAnywhere, Category = "Object")
	float Temperature = -1.0f;
	
	// Flammability of the object (affects ignition probability and fire spread)
	UPROPERTY(EditAnywhere, Category = "Object")
	float Flammability = -1.0f;

	// In the right conditions some objects can catch alight ig temp 
	UPROPERTY(EditAnywhere, Category = "Object")
	float SelfIgnitionChance = -1.0f;

	// What Fire This Object Creates
	UPROPERTY(EditAnywhere, Category = "Object")
	TSubclassOf<UBaseFireComponent> FireType;
};
