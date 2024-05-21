// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseObjectActor.h"
#include "Components/StaticMeshComponent.h" // Include for static mesh component
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "BaseEquipmentActor.generated.h"

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
    virtual float ScoreEquipment() const PURE_VIRTUAL(ABaseEquipmentActor::ScoreEquipment, return -1;);

protected:
    // Sound component for sound effects
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equipment")
    UAudioComponent* EquipmentSound;

    // Particle system component for particle effects
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equipment")
    UParticleSystemComponent* EquipmentParticles;
};
