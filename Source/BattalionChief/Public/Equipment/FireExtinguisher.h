// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEquipmentActor.h"
#include "ExtinguisherTypes/ExtinguisherProjectile.h"
#include "ExtinguisherTypes/BaseExtinguisherTypeComponent.h" // Assuming you have a base component for extinguisher types
#include "Components/ArrowComponent.h"
#include "Logging/LogMacros.h"
#include "FireExtinguisher.generated.h"

UCLASS()
class BATTALIONCHIEF_API AFireExtinguisher : public ABaseEquipmentActor
{
    GENERATED_BODY()
public:
    // Sets default values for this actor's properties
    AFireExtinguisher();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Uses the equipment
    virtual void UseEquipment()  override;

    // Checks if the equipment can be used
    virtual bool CanUseEquipment() const override;

    // Returns a score for the equipment based on situation, used by captains
    virtual float ScoreEquipment() const override;

    UFUNCTION(BlueprintCallable, CallInEditor, Category = Extinguisher)
    void Spray();

    void SpawnProjectile();
   
    UFUNCTION(BlueprintCallable, CallInEditor, Category = Extinguisher)
    void FillTank();

    bool IsTankEmpty() const;

    void LaunchProjectile(AExtinguisherProjectile* InProjectile, const FVector& InVector);

protected:
    UPROPERTY(EditAnywhere, Category = Extinguisher)
    UBaseExtinguisherTypeComponent* ExtinguisherTypeComponent;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    TSubclassOf<AExtinguisherProjectile> ExtinguisherProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extinguisher)
    UArrowComponent* ProjectileSpawn;

    // Capacity of the extinguisher tank (in liters)
    UPROPERTY(EditAnywhere, Category = Extinguisher)
    float TankCapacity = 10.0f;

    // Current level of extinguishing agent in the tank (in liters)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extinguisher)
    float CurrentTankLevel = TankCapacity;

    // How many liters are consumed per use
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Extinguisher)
    float ConsumptionRate = 0.1f; 

    // Range of the extinguisher (in meters)
    UPROPERTY(EditAnywhere, Category = Extinguisher)
    float Range = 100; 

    // SprayMaxAngle creating a Spray
    UPROPERTY(EditAnywhere, Category = Extinguisher)
    float SprayMaxAngle = 45.0f; 

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    int ProjectilesPerSpray = 30;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    float VelocityMultiplier = 10;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    FVector Origin;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    FVector ProjectileScale = FVector(.1f);
    
    UPROPERTY(EditAnywhere, Category = Extinguisher)
    FVector LaunchVelocity;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    FVector Direction;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    float Radians = SprayMaxAngle;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    int32 NumSides = 12;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    FLinearColor Color = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    bool bPersistentLines = false;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    float LifeTime = 35;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    uint8 DepthPriority = 0;

    UPROPERTY(EditAnywhere, Category = Extinguisher)
    float Thickness = 1;
};
