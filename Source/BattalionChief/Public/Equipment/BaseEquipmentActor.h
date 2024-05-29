// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseObjectActor.h"
#include "Components/StaticMeshComponent.h" // Include for static mesh component
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "BaseEquipmentActor.generated.h"


// This game is based on realism and in most cases firefighters will only take one or two things in their hands but certain things can be stored and this is useful to have
UENUM(BlueprintType)
enum class EEquipmentSize : uint8
{
    Error, 
    Small,      // Small-sized equipment, I.E flashlight, compass, tic, can easily be put in a pocket and wont take allot of space
    Medium,     // Medium-sized equipment, I.E. Halligan, Crowbar, Haligan bar. Conversion = Small slots 2:1 Medium slots
    Large,      // Large-sized equipment, I.E Hose, Firefighter Axe, Fire extinguisher. PPE. Hard to store on a person but not impossible. Conversion = Medium Slots 2:1 large slot
    ExtraLarge  // Extra-large equipment, I.E Spreaders, vehicle jack, air bags- cant really be stored on personage. Conversion = 2 Large Slots:1 Extra Large slot
};


USTRUCT()
struct FConversionMapStruct
{
    GENERATED_BODY()

public:
    FConversionMapStruct() {};
    FConversionMapStruct(const TMap<EEquipmentSize, int>& InMap);
    int GetConversion(EEquipmentSize InSize) const;

    protected:
    UPROPERTY(EditAnywhere, Category = Equipment)
    TMap<EEquipmentSize, int> ConversionMap;
};

UCLASS()
class BATTALIONCHIEF_API ABaseEquipmentActor : public ABaseObjectActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseEquipmentActor();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Uses the equipment
    virtual void UseEquipment() PURE_VIRTUAL(ABaseEquipmentActor::UseEquipment,);

    // Checks if the equipment can be used
    virtual bool CanUseEquipment() const PURE_VIRTUAL(ABaseEquipmentActor::CanUseEquipment, return false;);
 
    // Returns a score for the equipment based on situation, used by captains
    virtual float ScoreEquipment() const PURE_VIRTUAL(ABaseEquipmentActor::ScoreEquipment, return INDEX_NONE;);

    int GetSlotConversion(EEquipmentSize InCurrentSize, EEquipmentSize InDesiredSize) const;

protected:
    UPROPERTY(EditAnywhere, Category = Equipment)
    TMap<EEquipmentSize, FConversionMapStruct> ConversionMap;

    UPROPERTY(EditAnywhere, Category = Equipment)
    EEquipmentSize Size;

    // Only used by objects that can be held
    UPROPERTY(EditAnywhere, Category = Equipment)
    int Hands = INDEX_NONE;

    // Sound component for sound effects
    UPROPERTY(EditAnywhere, Category = Equipment)
    UAudioComponent* EquipmentSound;

    // Particle system component for particle effects
    UPROPERTY(EditAnywhere, Category = Equipment)
    UParticleSystemComponent* EquipmentParticles;

};
