// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtinguisherTypes/ExtinguisherProjectile.h"
#include "Objects/BaseObjectActor.h"
#include "Fires/BaseFireActor.h"
#include "Equipment/FireExtinguisher.h"

// Sets default values
AExtinguisherProjectile::AExtinguisherProjectile()
{

	PrimaryActorTick.bCanEverTick = true;

	ExtinguisherProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtinguisherProjectileMesh"));
	ExtinguisherProjectileMesh->SetSimulatePhysics(true);
	ExtinguisherProjectileMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ExtinguisherProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	ExtinguisherProjectileMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ExtinguisherProjectileMesh->SetGenerateOverlapEvents(true);
	ExtinguisherProjectileMesh->SetNotifyRigidBodyCollision(true);

	SetRootComponent(ExtinguisherProjectileMesh);

	//ExtinguisherProjectileMesh->SetupAttachment(RootComponent);

	// Create the audio component
	ExtinguisherProjectileSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ExtinguisherProjectileSound"));
	ExtinguisherProjectileSound->SetupAttachment(RootComponent);

	// Create the particle system component
	ExtinguisherProjectileParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExtinguisherProjectileParticles"));
	ExtinguisherProjectileParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AExtinguisherProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AExtinguisherProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime += DeltaTime;

	// Check if the lifetime exceeds the maximum allowed time
	if (LifeTime > MaxLifeTime)
	{
		Destroy();
	}
}

void AExtinguisherProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, OtherActor, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (!OtherActor || OtherActor == this)
		return;

	ABaseObjectActor* hit_object = Cast<ABaseObjectActor>(OtherActor);
	UBaseFireComponent* hit_fire = Cast<UBaseFireComponent>(OtherActor);
	AExtinguisherProjectile* hit_projectile = Cast<AExtinguisherProjectile>(OtherActor);
	if (hit_projectile)
		return;

	FString debug_message = FString::Printf(TEXT("AExtinguisherProjectile::NotifyHit    %s has been hit by %s"), *GetName(), *OtherActor->GetName());

	if (hit_object)
	{
		UE_LOG(LogFireExtinguisher, Log, TEXT("%s"), *debug_message);


	}

	if (hit_fire)
	{
		hit_fire->Extinguish(ExtinguisherType);
		UE_LOG(LogFireExtinguisher, Log, TEXT("%s"), *debug_message);
	}
	Destroy();
}

void AExtinguisherProjectile::CreateExtinguisherTypeComponent(const TSubclassOf<UBaseExtinguisherTypeComponent>& InBaseExtinguisherTypeComponentClass)
{
	ExtinguisherType = NewObject<UBaseExtinguisherTypeComponent>(this, InBaseExtinguisherTypeComponentClass);
}

