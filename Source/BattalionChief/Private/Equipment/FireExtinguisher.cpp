#include "Equipment/FireExtinguisher.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ExtinguisherTypes/ExtinguisherProjectile.h"
#include "Components/SceneComponent.h"

// Sets default values
AFireExtinguisher::AFireExtinguisher() : ABaseEquipmentActor()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set up the extinguisher type component
	ExtinguisherTypeComponent = CreateDefaultSubobject<UBaseExtinguisherTypeComponent>(TEXT("ExtinguisherTypeComponent"));
	ProjectileSpawn = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFireExtinguisher::BeginPlay()
{
	Super::BeginPlay();
	FillTank();
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
	if (IsTankEmpty())
		return;

	CurrentTankLevel -= ConsumptionRate;
	Origin = ProjectileSpawn->GetComponentLocation();
	Direction =  ProjectileSpawn->GetComponentRotation().Vector();
	UWorld* world = GetWorld();
	Radians = FMath::DegreesToRadians(SprayMaxAngle);

	DrawDebugCone(world, Origin, Direction, Range, Radians, Radians, NumSides, Color.ToFColor(true), bPersistentLines, LifeTime, DepthPriority, Thickness);

	for (int i = 0; i < ProjectilesPerSpray; i++)
	{
		SpawnProjectile();
	}
}

void AFireExtinguisher::SpawnProjectile()
{
	// Spawn the projectile
	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AExtinguisherProjectile* spawned_projectile = GetWorld()->SpawnActor<AExtinguisherProjectile>(ExtinguisherProjectileClass, Origin, FRotator::ZeroRotator, spawn_params);

	if (!spawned_projectile)
	{
		UE_LOG(LogFireExtinguisher, Error, TEXT("void AFireExtinguisher::SpawnProjectile() Failed to spawn projectile"));
		return;
	}

	spawned_projectile->SetActorScale3D(Scale);
	FVector random_cone_direction = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(Direction, SprayMaxAngle);

	// Spawn and attach extinguisher type component to spawned projectile
	if (ExtinguisherTypeComponent)
	{
		spawned_projectile->CreateExtinguisherTypeComponent(ExtinguisherTypeComponent->GetClass());
	}
	else
	{
		UE_LOG(LogFireExtinguisher, Error, TEXT("void AFireExtinguisher::SpawnProjectile() ExtinguisherTypeComponent is not set in SpawnProjectile."));
	}

	LaunchProjectile(spawned_projectile, random_cone_direction);
}

void AFireExtinguisher::FillTank()
{
	CurrentTankLevel = TankCapacity;
}

bool AFireExtinguisher::IsTankEmpty() const
{
	return CurrentTankLevel <= 0;
}

void AFireExtinguisher::LaunchProjectile(AExtinguisherProjectile* InProjectile, const FVector& InVector)
{
	FVector launch_velocity = InVector * Range * VelocityMultiplier;
	InProjectile->GetObjectMesh()->AddImpulse(launch_velocity, NAME_None, true);
}
