// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseObjectActor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "ExtinguisherTypes/BaseExtinguisherTypeComponent.h"
#include "ExtinguisherProjectile.generated.h"

UCLASS()
class BATTALIONCHIEF_API AExtinguisherProjectile : public ABaseObjectActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtinguisherProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void CreateExtinguisherTypeComponent(const TSubclassOf<UBaseExtinguisherTypeComponent>& InBaseExtinguisherTypeComponentClass);

protected:
	UBaseExtinguisherTypeComponent* ExtinguisherType;

	UPROPERTY(VisibleAnywhere, Category = "Extinguisher Projectile")
	float LifeTime;

	UPROPERTY(VisibleAnywhere, Category = "Extinguisher Projectile")
	float MaxLifeTime = 30;

	// Sound component for sound effects
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Extinguisher Projectile")
	UAudioComponent* ExtinguisherProjectileSound;

	// Particle system component for particle effects
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Extinguisher Projectile")
	UParticleSystemComponent* ExtinguisherProjectileParticles;
};
