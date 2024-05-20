// Fill out your copyright notice in the Description page of Project Settings.


#include "Fires/ClassAFire.h"
#include "ExtinguisherTypes/ABCPowder.h"
#include "ExtinguisherTypes/BCPowder.h"
#include "ExtinguisherTypes/CarbonDioxide.h"
#include "ExtinguisherTypes/ClassD.h"
#include "ExtinguisherTypes/Foam.h"
#include "ExtinguisherTypes/Water.h"
#include "ExtinguisherTypes/WetChemical.h"

AClassAFire::AClassAFire()
{
    // Initialize the helpful extinguisher types map with their extinguishing percentages
    HelpfulExtinguisherTypesMap.Add(UABCPowder::StaticClass(), 0.9f);              // ABC Powder extinguisher is 90% effective
    HelpfulExtinguisherTypesMap.Add(UBCPowder::StaticClass(), 0.85f);               // BC Powder extinguisher is 85% effective
    HelpfulExtinguisherTypesMap.Add(UCarbonDioxide::StaticClass(), 0.95f);         // Carbon Dioxide extinguisher is 95% effective
    HelpfulExtinguisherTypesMap.Add(UClassD::StaticClass(), 0.8f);                    // Class D extinguisher is 80% effective
    HelpfulExtinguisherTypesMap.Add(UFoam::StaticClass(), 0.7f);                     // Foam extinguisher is 70% effective
    HelpfulExtinguisherTypesMap.Add(UWater::StaticClass(), 0.8f);                    // Water extinguisher is 80% effective
    HelpfulExtinguisherTypesMap.Add(UWetChemical::StaticClass(), 0.9f);              // Wet Chemical extinguisher is 90% effective
}
