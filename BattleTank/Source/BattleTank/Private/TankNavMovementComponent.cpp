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
	//no need to call super and inherit from the parent class implementation.
	auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIVectorIntention = MoveVelocity.GetSafeNormal();

	auto ZarbeDakheli = FVector::DotProduct(TankForwardVector, AIVectorIntention);// is a measure of how closely two vectors align, in terms of the directions they point.
	auto ZarbeBordari = FVector::CrossProduct(TankForwardVector, AIVectorIntention);//gives us a Z vector between -1 and 1 and we dont rotate if 0, right and left if 1 and -1
	IntendMoveForward(ZarbeDakheli);
	TurnRight(ZarbeBordari.Z);
}

