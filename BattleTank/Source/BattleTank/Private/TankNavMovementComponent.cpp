// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankNavMovementComponent.h"

void UTankNavMovementComponent::IntendMoveForward(float UserInput)
{
	// auto Time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%f UserInput = %f"),Time, UserInput);

	RightTrack->SetThrottle(UserInput);
	LeftTrack->SetThrottle(UserInput);
}

void UTankNavMovementComponent::Initialize(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
	if (!RightTrackToSet || !LeftTrackToSet) { return; }
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

