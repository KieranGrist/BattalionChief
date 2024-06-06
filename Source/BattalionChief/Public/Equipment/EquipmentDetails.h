// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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


class ABaseEquipmentActor;

// Slot the equipment will go in when equipped
UENUM(BlueprintType)
enum class ECharacterEquipmentSlotType : uint8
{
    Error        UMETA(DisplayName = "Error"),
    Helmet       UMETA(DisplayName = "Helmet"),
    Face         UMETA(DisplayName = "Face"),
    Torso        UMETA(DisplayName = "Torso"),
    Legs         UMETA(DisplayName = "Legs"),
    BothHands     UMETA(DisplayName = "Both Hands"),
    LeftHand     UMETA(DisplayName = "Left Hand"),
    RightHand    UMETA(DisplayName = "Right Hand")
};

USTRUCT()
struct FBaseCharacterEquipmentSlot
{

    GENERATED_BODY()

public:
    FBaseCharacterEquipmentSlot() {}

    FBaseCharacterEquipmentSlot(ECharacterEquipmentSlotType InCharacterEquipmentSlotType, FName InSocketName);
   
    static float GetSlotConversion(EEquipmentSize InCurrentSize, EEquipmentSize InDesiredSize);

    void SpawnEquipment();
   
    void SetupSocket(USkeletalMeshComponent* InCharacterMesh);

    void AttachEquipment(ABaseEquipmentActor* InEquipment);

    void DetachEquipment();

    // Getter and Setter for CharacterEquipmentSlotType
    ECharacterEquipmentSlotType GetCharacterEquipmentSlotType() const;
   
    void SetCharacterEquipmentSlotType(ECharacterEquipmentSlotType InCharacterEquipmentSlotType);

    // Getter and Setter for CharacterMesh
    USkeletalMeshComponent* GetCharacterMesh() const;

    // Getter and Setter for Socket
    const USkeletalMeshSocket* GetSocket() const;

    // Getter and Setter for SocketName
    const FName& GetSocketName() const;
   
    void SetSocketName(const FName& InSocketName);

    // Getter and Setter for Equipment
    ABaseEquipmentActor* GetEquipment() const;
   
    void SetEquipment(ABaseEquipmentActor* InEquipment);

    // Getter and Setter for SpawnEquipment
    const TSubclassOf<ABaseEquipmentActor>& GetSpawnEquipmentClass() const;
    
    void SetSpawnEquipmentClass(const TSubclassOf<ABaseEquipmentActor>& InSpawnEquipment);

    // Getter and Setter for Index
    int32 GetIndex() const;
    
    void SetIndex(int32 InIndex);

protected:
    UPROPERTY(EditAnywhere, Category = Equipment)
    ECharacterEquipmentSlotType CharacterEquipmentSlotType = ECharacterEquipmentSlotType::Helmet;

    UPROPERTY(EditAnywhere, Category = Equipment)
    USkeletalMeshComponent* CharacterMesh;
    
    UPROPERTY(EditAnywhere, Category = Equipment)
    const USkeletalMeshSocket* Socket;

    UPROPERTY(EditAnywhere, Category = Equipment)
    FName SocketName = FName("HelmetSocket");

    UPROPERTY(EditAnywhere, Category = Equipment)
    ABaseEquipmentActor* Equipment;

    UPROPERTY(EditAnywhere, Category = Equipment)
    TSubclassOf<ABaseEquipmentActor> SpawnEquipmentClass;

    UPROPERTY(EditAnywhere, Category = Equipment)
    int32 Index =  INDEX_NONE;
};

USTRUCT()
struct FPocketEquipment : public FBaseCharacterEquipmentSlot
{

    GENERATED_BODY()

public:
    
    FPocketEquipment() {}

    FPocketEquipment(ECharacterEquipmentSlotType InCharacterEquipmentSlotType, FName InSocketName);

    void AddEquipmentToPocket();

    UPROPERTY(EditAnywhere, Category = Pocket)
    EEquipmentSize PocketSize;

    UPROPERTY(EditAnywhere, Category = Pocket)
    int32 PocketCapacity;

    UPROPERTY(EditAnywhere, Category = Pocket)
    TMap<int32, FVector> PocketOffsetMap;
    
    UPROPERTY(EditAnywhere, Category = Pocket)
    TMap<int32, FBaseCharacterEquipmentSlot> StoredEquipmentMap;
};
