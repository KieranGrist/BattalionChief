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


	ConversionMap =
	{
		{
			EEquipmentSize::Small, FConversionMapStruct({
													{ EEquipmentSize::Small, 1 },
													{ EEquipmentSize::Medium, 2 },
													{ EEquipmentSize::Large, 4 },
													{ EEquipmentSize::ExtraLarge, 8 }
													})},
		{
			EEquipmentSize::Medium, FConversionMapStruct({
													{ EEquipmentSize::Small, 2 },
													{ EEquipmentSize::Medium, 1 },
													{ EEquipmentSize::Large, 2 },
													{ EEquipmentSize::ExtraLarge, 4 }
													})},
		{
			EEquipmentSize::Large, FConversionMapStruct({
													{ EEquipmentSize::Small, 4 },
													{ EEquipmentSize::Medium, 2 },
													{ EEquipmentSize::Large, 1 },
													{ EEquipmentSize::ExtraLarge, 2 }
													})},
		{
			EEquipmentSize::ExtraLarge, FConversionMapStruct({
													{ EEquipmentSize::Small, 8 },
													{ EEquipmentSize::Medium, 4 },
													{ EEquipmentSize::Large, 2 },
													{ EEquipmentSize::ExtraLarge, 1 }
													})},
	};
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

FConversionMapStruct::FConversionMapStruct(const TMap<EEquipmentSize, int>& InMap)
{
	ConversionMap = InMap;
}

int FConversionMapStruct::GetConversion(EEquipmentSize InSize) const
{
	const int* found_conversion = ConversionMap.Find(InSize);

	if (!found_conversion)
		return INDEX_NONE;
	return *found_conversion;
}

int ABaseEquipmentActor::GetSlotConversion(EEquipmentSize InCurrentSize, EEquipmentSize InDesiredSize) const
{
	auto found_map = ConversionMap.Find(InCurrentSize);
	if (!found_map)
		return INDEX_NONE;
	const FConversionMapStruct& map = *found_map;
	return map.GetConversion(InDesiredSize);
}


EEquipmentSize ABaseEquipmentActor::GetEquipmentSize() const
{
	return EquipmentSize;
}

ECharacterEquipmentSlot ABaseEquipmentActor::GetCharacterEquipmentSlot() const
{
	return CharacterEquipmentSlot;
}

const FVector& ABaseEquipmentActor::GetSlotRelativeGap() const
{
	return SlotRelativeGap;
}

const FRotator& ABaseEquipmentActor::GetSlotRelativeRotation() const
{
	return SlotRelativeRotation;
}

int ABaseEquipmentActor::GetHands() const
{
	return Hands;
}
