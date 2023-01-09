// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), HideCategories = ("Collision", "HLOD", "Rendering", "Physics", "Navigation", "VirtualTexture" ))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void ElevateBarrel(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = "Setup For Designer")
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = "Setup For Designer")
	float MaxElevationDegrees = 0;
	UPROPERTY(EditAnywhere, Category = "Setup For Designer")
	float MinElevationDegrees = 0;
};
