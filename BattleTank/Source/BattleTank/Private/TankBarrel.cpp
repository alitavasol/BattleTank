// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float DegreesPerSecond)
{
	//Move the barrel right amount this frame
	//Given max elevation speed and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Trying To elevate Barrel At Speed of %f"), DegreesPerSecond);
}
