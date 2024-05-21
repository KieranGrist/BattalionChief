// Fill out your copyright notice in the Description page of Project Settings.


#include "Fires/Smoke.h"

// Sets default values
USmoke::USmoke() :UBaseFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void USmoke::BeginPlay()
{
	Super::BeginPlay();
	
}

void USmoke::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}