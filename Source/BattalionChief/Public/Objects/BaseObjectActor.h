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

	void SetupObjectMeshMaterial();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to apply damage to this object
	UFUNCTION(BlueprintCallable, Category = Object)
	void ApplyDamage(float InDamageAmount);

	// Function to ignite the object with a specific fire
	UFUNCTION(BlueprintCallable, Category = Object)
	void IgniteFire(UBaseFireComponent* InFire);

	UFUNCTION(BlueprintCallable, Category = Object)
	void CalculateTemperature();

	UFUNCTION(BlueprintCallable, Category = Object)
	void CalculateFlammability();

	UFUNCTION(BlueprintCallable, Category = Object)
	void CalculateSelfIgnitionChance();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = Object)
	void SelfIgniteFire();
	
	UFUNCTION(BlueprintCallable, Category = Object)
	void SetupFireComponent();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = Object)
	void ExtinguishFire();

	UFUNCTION(BlueprintImplementableEvent, Category = Object)
	void OnObjectDestroyed_BP();

	UFUNCTION(BlueprintCallable, Category = Object)
	bool IsOnFire();

	UFUNCTION(BlueprintCallable, Category = Object)
	virtual void StartFireEffects();
	
	UFUNCTION(BlueprintCallable, Category = Object)
	virtual void StopFireEffects();

	// Event dispatcher to notify when the object is destroyed
	UPROPERTY(BlueprintAssignable, Category = Object)
	FOnObjectDestroyedSignature OnObjectDestroyed;

	// Static mesh component for equipment model
	UFUNCTION(BlueprintCallable, Category = Object)
	UStaticMeshComponent* GetObjectMesh() const;

	// Particle system for visual representation of fire
	UFUNCTION(BlueprintCallable, Category = Object)
	UParticleSystemComponent* GetFireParticles() const;

	// Audio component for fire sound effects
	UFUNCTION(BlueprintCallable, Category = Object)
	UAudioComponent* GetFireSound() const;

	UFUNCTION(BlueprintCallable, Category = Object)
	UBaseFireComponent* GetFireComponent() const;

	// Health of the object
	UFUNCTION(BlueprintCallable, Category = Object)
	float GetHealth() const;

	// Weight of the object in grams (affects fire spread and intensity)
	UFUNCTION(BlueprintCallable, Category = Object)
	float GetWeight() const;

	// Objects Current Temperature in Degrees
	UFUNCTION(BlueprintCallable, Category = Temperature)
	float GetTemperature() const;

	// Represents the ability of the object to conduct heat. Higher values indicate better heat conduction.
	UFUNCTION(BlueprintCallable, Category = Temperature)
	float GetThermalConductivity() const;

	// Represents the amount of heat required to raise the temperature of the object by one degree. Higher values mean the object requires more heat energy to increase its temperature.
	UFUNCTION(BlueprintCallable, Category = Temperature)
	float GetSpecificHeatCapacity() const;

	// Represents the starting temperature of the object. Define the normal temperature.
	UFUNCTION(BlueprintCallable, Category = Temperature)
	float GetInitialTemperature() const;

	// Flammability of the object (affects ignition probability and fire spread)
	UFUNCTION(BlueprintCallable, Category = Fire)
	float GetFlammability() const;

	// In the right conditions some objects can catch alight ig temp 
	UFUNCTION(BlueprintCallable, Category = Fire)
	float GetSelfIgnitionChance() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	TMap<FName, FLinearColor>  VectorParameterValueMap = { {FName("Color"), FLinearColor(0, 0, 0, 1)} };

	// Static mesh component for equipment model
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object)
	UStaticMeshComponent* ObjectMesh;

	// Particle system for visual representation of fire
	UPROPERTY(EditAnywhere, Category = Fire)
	UParticleSystemComponent* FireParticles;

	// Audio component for fire sound effects
	UPROPERTY(EditAnywhere, Category = Fire)
	UAudioComponent* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fire)
	UBaseFireComponent* FireComponent;

	// Health of the object
	UPROPERTY(EditAnywhere, Category = Object)
	float Health = INDEX_NONE;

	// Weight of the object in grams (affects fire spread and intensity)
	UPROPERTY(EditAnywhere, Category = Object)
	float Weight = INDEX_NONE;

	// Objects Current Temperature in Degrees
	UPROPERTY(EditAnywhere, Category = Temperature)
	float Temperature = INDEX_NONE;
	
	// Represents the ability of the object to conduct heat. Higher values indicate better heat conduction.
	UPROPERTY(EditAnywhere, Category = Temperature)
	float ThermalConductivity = INDEX_NONE;

	// Represents the amount of heat required to raise the temperature of the object by one degree. Higher values mean the object requires more heat energy to increase its temperature.
	UPROPERTY(EditAnywhere, Category = Temperature)
	float SpecificHeatCapacity = INDEX_NONE;

	// Represents the starting temperature of the object. Define the normal temperature.
	UPROPERTY(EditAnywhere, Category = Temperature)
	float InitialTemperature = INDEX_NONE;

	// Flammability of the object (affects ignition probability and fire spread)
	UPROPERTY(EditAnywhere, Category = Fire)
	float Flammability = INDEX_NONE;

	// In the right conditions some objects can catch alight ig temp 
	UPROPERTY(EditAnywhere, Category = Fire)
	float SelfIgnitionChance = INDEX_NONE;

	// What Fire This Object Creates
	UPROPERTY(EditAnywhere, Category = Fire)
	TSubclassOf<UBaseFireComponent> CreatedFire = UBaseFireComponent::StaticClass();
};
