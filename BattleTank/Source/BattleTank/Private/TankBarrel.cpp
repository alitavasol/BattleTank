// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	//Move the barrel right amount this frame
	//Given max elevation speed and the frame time
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto ClampedRawNewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	this->SetRelativeRotation(FRotator(ClampedRawNewElevation,0,0));
}
