// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankNavMovementComponent.h"

void UTankNavMovementComponent::IntendMoveForward(float UserInput)
{
	RightTrack->SetThrottle(UserInput);
	LeftTrack->SetThrottle(UserInput);
}

void UTankNavMovementComponent::TurnRight(float UserInput)
{
	RightTrack->SetThrottle(-UserInput);
	LeftTrack->SetThrottle(UserInput);
}

void UTankNavMovementComponent::Initialize(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	auto Time = GetWorld()->TimeSeconds;
	UE_LOG(LogTemp,Warning,TEXT("%f Name = %s and Move Velocity = %s"),Time, *TankName, *MoveVelocity.ToString())
}

