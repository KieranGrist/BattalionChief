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

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Spray")
    void Spray();

    void SpawnProjectile();
   
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Extinguisher")
    void FillTank();

    bool IsTankEmpty() const;

    void LaunchProjectile(AExtinguisherProjectile* InProjectile, const FVector& InVector);

protected:
    UPROPERTY(EditAnywhere, Category = "Extinguisher")
    UBaseExtinguisherTypeComponent* ExtinguisherTypeComponent;

    UPROPERTY(EditAnywhere, Category = "Spray")
    TSubclassOf<AExtinguisherProjectile> ExtinguisherProjectileClass;

    // Capacity of the extinguisher tank (in liters)
    UPROPERTY(EditAnywhere, Category = "Extinguisher")
    float TankCapacity = 10.0f;

    // Current level of extinguishing agent in the tank (in liters)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extinguisher")
    float CurrentTankLevel = TankCapacity;

    // How many liters are consumed per use
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extinguisher")
    float ConsumptionRate = 0.1f; 

    // Range of the extinguisher (in meters)
    UPROPERTY(EditAnywhere, Category = "Spray")
    float Range = 100; 

    // SprayMaxAngle creating a Spray
    UPROPERTY(EditAnywhere, Category = "Spray")
    float SprayMaxAngle = 45.0f; 

    UPROPERTY(EditAnywhere, Category = "Spray")
    int ProjectilesPerSpray = 30;

    UPROPERTY(EditAnywhere, Category = "Spray")
    float VelocityMultiplier = 10;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    FVector Origin;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    FVector Scale = FVector(.1f);
    
    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    FVector LaunchVelocity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spray")
    UArrowComponent*  ProjectileSpawn;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    FVector Direction;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    float Radians = SprayMaxAngle;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    int32 NumSides = 12;

    UPROPERTY(EditAnywhere, Category = "Spray")
    FLinearColor Color = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    bool bPersistentLines = false;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    float LifeTime = 35;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    uint8 DepthPriority = 0;

    UPROPERTY(EditAnywhere, Category = "Spray|Debug")
    float Thickness = 1;
};
