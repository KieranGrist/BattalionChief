#include "EquipmentDetails.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/EquipmentDetails.h"
#include "Equipment/BaseEquipmentActor.h"

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

void FBaseCharacterEquipmentSlot::DetachEquipment()
{
    if (!Exuipment)
        return;
    Equipment->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    UStaticMeshComponent* object_mesh = Equipment->GetObjectMesh();
    object_mesh->SetSimulatePhysics(true);
    object_mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    object_mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    object_mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    object_mesh->SetGenerateOverlapEvents(true);
    object_mesh->SetNotifyRigidBodyCollision(true);

    Equipment = nullptr;
}


static float FBaseCharacterEquipmentSlot::GetSlotConversion(EEquipmentSize InCurrentSize, EEquipmentSize InDesiredSize)
{
    // Conversion rates based on slot size
    const float ConversionRates[][4] = {
        // Small  Medium  Large  ExtraLarge
        { 1.0f,   0.5f,   0.25f,  0.125f }, // Small
        { 2.0f,   1.0f,   0.5f,   0.25f  }, // Medium
        { 4.0f,   2.0f,   1.0f,   0.5f   }, // Large
        { 8.0f,   4.0f,   2.0f,   1.0f   }  // ExtraLarge
    };

    int32 CurrentSizeIndex = static_cast<int32>(InCurrentSize);
    int32 DesiredSizeIndex = static_cast<int32>(InDesiredSize);
    return ConversionRates[CurrentSizeIndex][DesiredSizeIndex];
}

// Getter and Setter for CharacterEquipmentSlotType
ECharacterEquipmentSlotType FBaseCharacterEquipmentSlot::GetCharacterEquipmentSlotType() const 
{
    return CharacterEquipmentSlotType; 
}

void FBaseCharacterEquipmentSlot::SetCharacterEquipmentSlotType(ECharacterEquipmentSlotType InCharacterEquipmentSlotType) 
{ 
    CharacterEquipmentSlotType = InCharacterEquipmentSlotType; 
}

// Getter and Setter for CharacterMesh
USkeletalMeshComponent* FBaseCharacterEquipmentSlot::GetCharacterMesh() const 
{ 
    return CharacterMesh;
}

// Getter and Setter for Socket
const USkeletalMeshSocket* FBaseCharacterEquipmentSlot::GetSocket() const 
{
    return Socket;
}

// Getter and Setter for SocketName
const FName& FBaseCharacterEquipmentSlot::GetSocketName() const 
{
    return SocketName; 
}

void FBaseCharacterEquipmentSlot::SetSocketName(const FName& InSocketName) 
{
    SocketName = InSocketName; 
}

// Getter and Setter for Equipment
ABaseEquipmentActor* FBaseCharacterEquipmentSlot::GetEquipment() const 
{ 
    return Equipment;
}

void FBaseCharacterEquipmentSlot::SetEquipment(ABaseEquipmentActor* InEquipment) 
{
    Equipment = InEquipment; 
}

// Getter and Setter for SpawnEquipment
const TSubclassOf<ABaseEquipmentActor>& FBaseCharacterEquipmentSlot::GetSpawnEquipmentClass() const 
{
    return SpawnEquipmentClass;
}

void FBaseCharacterEquipmentSlot::SetSpawnEquipmentClass(const TSubclassOf<ABaseEquipmentActor>& InSpawnEquipment) 
{
    SpawnEquipmentClass = InSpawnEquipment;
}

// Getter and Setter for Index
int32 FBaseCharacterEquipmentSlot::GetIndex() const 
{ 
    return Index; 
}

void FBaseCharacterEquipmentSlot::SetIndex(int32 InIndex) 
{ 
    Index = InIndex;
}

FPocketEquipment::FPocketEquipment(ECharacterEquipmentSlotType InCharacterEquipmentSlotType, FName InSocketName) : FBaseCharacterEquipmentSlot(InCharacterEquipmentSlotType, InSocketName)
{

}