// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "ExtinguisherProjectile.generated.h"

UCLASS()
class BATTALIONCHIEF_API AExtinguisherProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtinguisherProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// Static mesh component for equipment model
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Extinguisher Projectile")
	UStaticMeshComponent* ExtinguisherProjectileMesh;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Extinguisher Projectile")
	float LifeTime;

	UPROPERTY(VisibleAnywhere, Category = "Extinguisher Projectile")
	float MaxLifeTime = 300;

	// Sound component for sound effects
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Extinguisher Projectile")
	UAudioComponent* ExtinguisherProjectileSound;

	// Particle system component for particle effects
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Extinguisher Projectile")
	UParticleSystemComponent* ExtinguisherProjectileParticles;
};
