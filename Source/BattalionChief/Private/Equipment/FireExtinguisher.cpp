// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/FireExtinguisher.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFireExtinguisher::AFireExtinguisher()
{
    // Set up the extinguisher type component
    ExtinguisherTypeComponent = CreateDefaultSubobject<UBaseExtinguisherTypeComponent>(TEXT("ExtinguisherTypeComponent"));
    ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
    ProjectileSpawn->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFireExtinguisher::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AFireExtinguisher::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AFireExtinguisher::UseEquipment()
{
    Spray();
}

bool AFireExtinguisher::CanUseEquipment() const
{
    return IsTankEmpty();
}

float AFireExtinguisher::ScoreEquipment() const
{
    return Super::ScoreEquipment();
}

void AFireExtinguisher::Spray()
{
    Origin = ProjectileSpawn->GetComponentLocation();
    Direction = GetActorForwardVector();
    UWorld* world = GetWorld();
 
    Radians = FMath::DegreesToRadians(SprayMaxAngle);
    DrawDebugCone(world, Origin, Direction, Range, FMath::DegreesToRadians(SprayMaxAngle), FMath::DegreesToRadians(SprayMaxAngle), NumSides, Color.ToFColor(true), bPersistentLines, LifeTime, DepthPriority, Thickness);

    for (int i = 0; i < ProjectilesPerSpray; i++)
    {
        SpawnProjectile();
    }
}

void AFireExtinguisher::SpawnProjectile()
{
    // Spawn the projectile
    AExtinguisherProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AExtinguisherProjectile>(ExtinguisherProjectileClass, Origin, FRotator::ZeroRotator);
    SpawnedProjectile->SetActorScale3D(Scale);
    FVector RandomConeDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(Direction, SprayMaxAngle);
    LaunchProjectile(SpawnedProjectile, RandomConeDirection);   
}

void AFireExtinguisher::FillTank()
{
    CurrentTankLevel = TankCapacity;
}

bool AFireExtinguisher::IsTankEmpty() const
{
    return CurrentTankLevel <= TankCapacity;
}

void AFireExtinguisher::LaunchProjectile(AExtinguisherProjectile* InProjectile, const FVector& InVector)
{
    LaunchVelocity = InVector * Range * VelocityMultiplier;
    InProjectile->ExtinguisherProjectileMesh->AddImpulse(LaunchVelocity, NAME_None, true);
}
