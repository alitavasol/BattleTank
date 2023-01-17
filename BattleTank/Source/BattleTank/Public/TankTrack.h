// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Sets throttle to left or right track based on user input to move right or left.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//sets throttle to -1 and 1.
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
};
