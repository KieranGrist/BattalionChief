// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquipmentDetails.h"
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
    UFUNCTION(BlueprintCallable, Category = Equipment)
    virtual void UseEquipment() PURE_VIRTUAL(ABaseEquipmentActor::UseEquipment,);

    // Checks if the equipment can be used
    UFUNCTION(BlueprintCallable, Category = Equipment)
    virtual bool CanUseEquipment() const PURE_VIRTUAL(ABaseEquipmentActor::CanUseEquipment, return false;);
 
    // Returns a score for the equipment based on situation, used by captains
    UFUNCTION(BlueprintCallable, Category = Equipment)
    virtual float ScoreEquipment() const PURE_VIRTUAL(ABaseEquipmentActor::ScoreEquipment, return INDEX_NONE;);
    
    UFUNCTION(BlueprintCallable, Category = Equipment)
    int32 GetSlotConversion(EEquipmentSize InCurrentSize, EEquipmentSize InDesiredSize) const;

    UFUNCTION(BlueprintCallable, Category = Equipment)
    EEquipmentSize GetEquipmentSize() const;

    UFUNCTION(BlueprintCallable, Category = Equipment)
    ECharacterEquipmentSlotType GetCharacterEquipmentSlot() const;

    UFUNCTION(BlueprintCallable, Category = Equipment)
    const FVector& GetSlotRelativeGap() const;

    UFUNCTION(BlueprintCallable, Category = Equipment)
    const FRotator& GetSlotRelativeRotation() const;

    UFUNCTION(BlueprintCallable, Category = Equipment)
    void SetSlotRelativeGap(const FVector& InSlotRelativeGap);

    UFUNCTION(BlueprintCallable, Category = Equipment)
    void SetSlotRelativeRotation(const FRotator& InSlotRelativeRotation);

    UFUNCTION(BlueprintCallable, Category = Equipment)
    int32 GetHands() const;

protected:
    UPROPERTY(EditAnywhere, Category = Equipment)
    EEquipmentSize EquipmentSize;

    UPROPERTY(EditAnywhere, Category = Equipment)
    ECharacterEquipmentSlotType CharacterEquipmentSlot;

    UPROPERTY(EditAnywhere, Category = Equipment)
    FVector SlotRelativeGap;
    
    UPROPERTY(EditAnywhere, Category = Equipment)
    FRotator SlotRelativeRotation;

    // Only used by objects that can be held
    UPROPERTY(EditAnywhere, Category = Equipment)
    int32 Hands = INDEX_NONE;

    // Sound component for sound effects
    UPROPERTY(EditAnywhere, Category = Equipment)
    UAudioComponent* EquipmentSound;

    // Particle system component for particle effects
    UPROPERTY(EditAnywhere, Category = Equipment)
    UParticleSystemComponent* EquipmentParticles;
};
