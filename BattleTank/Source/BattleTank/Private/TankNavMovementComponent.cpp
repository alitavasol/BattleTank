// Fill out your copyright notice in the Description page of Project Settings.


#include "TankNavMovementComponent.h"

void UTankNavMovementComponent::IntendMoveForward(float UserInput)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f UserInput = %f"),Time, UserInput);
}
