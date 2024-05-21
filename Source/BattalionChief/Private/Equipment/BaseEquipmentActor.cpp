// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseEquipmentActor.h"
// Sets default values
ABaseEquipmentActor::ABaseEquipmentActor() : ABaseObjectActor()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = false;

    // Create the equipment sound component and attach it to the root component
    EquipmentSound = CreateDefaultSubobject<UAudioComponent>(TEXT("EquipmentSound"));
    EquipmentSound->SetupAttachment(RootComponent);

    // Create the equipment particles component and attach it to the root component
    EquipmentParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EquipmentParticles"));
    EquipmentParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseEquipmentActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABaseEquipmentActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

