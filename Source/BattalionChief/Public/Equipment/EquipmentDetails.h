// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


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
   
    void SpawnEquipment();
   
    void SetupSocket(USkeletalMeshComponent* InCharacterMesh);

    void AttachEquipment(ABaseEquipmentActor* InEquipment);
  
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
    TSubclassOf<ABaseEquipmentActor> SpawnEquipment;

    UPROPERTY(EditAnywhere, Category = Equipment)
    int32 Index =  INDEX_NONE;
};

FBaseCharacterEquipmentSlot::FBaseCharacterEquipmentSlot(ECharacterEquipmentSlotType InCharacterEquipmentSlotType, FName InSocketName)
{
    CharacterEquipmentSlotType = InCharacterEquipmentSlotType;
    SocketName = InSocketName;
}

void FBaseCharacterEquipmentSlot::SpawnEquipment()
{

}

void FBaseCharacterEquipmentSlot::SetupSocket(USkeletalMeshComponent* InCharacterMesh)
{
    CharacterMesh = InCharacterMesh;
    if (!CharacterMesh)
        return;

    Socket = CharacterMesh->GetSocketByName(SocketName);
}

void FBaseCharacterEquipmentSlot::AttachEquipment(ABaseEquipmentActor* InEquipment)
{
    Equipment = InEquipment;

    if (!Equipment)
        return;

    UStaticMeshComponent* object_mesh = Equipment->GetObjectMesh();
    object_mesh->SetSimulatePhysics(false);
    object_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    object_mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    object_mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    object_mesh->SetGenerateOverlapEvents(false);
    object_mesh->SetNotifyRigidBodyCollision(false);

    Socket->AttachActor(Equipment, CharacterMesh);

    Equipment->SetActorRelativeLocation(Equipment->GetSlotRelativeGap());
    Equipment->SetActorRelativeRotation(Equipment->GetSlotRelativeRotation());
}

USTRUCT()
struct FPocketEquipment : public FBaseCharacterEquipmentSlot
{

    GENERATED_BODY()

public:
    
    FPocketEquipment() {}

    int32 MaxPockets = 4;

    TMap<int32, FVector> PocketOffsetMap;
    
    TMap<int32, FBaseCharacterEquipmentSlot> StoredEquipmentMap;
};