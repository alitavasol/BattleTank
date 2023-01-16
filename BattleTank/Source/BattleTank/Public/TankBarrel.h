// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))//, HideCategories = ("Collision", "HLOD", "Rendering", "Physics", "Navigation", "VirtualTexture" ))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void ElevateBarrel(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup For Designer")
	float MaxDegreesPerSecond = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Setup For Designer")
	float MaxElevationDegrees = 40;
	UPROPERTY(EditDefaultsOnly, Category = "Setup For Designer")
	float MinElevationDegrees = 0;
};
