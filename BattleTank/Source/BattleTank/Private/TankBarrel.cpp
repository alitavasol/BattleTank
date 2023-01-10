// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	//Move the barrel right amount this frame
	//Given max elevation speed and the frame time
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Time: %f Trying To elevate Barrel At Speed of %f"),Time, RelativeSpeed);
}
