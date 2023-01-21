// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	// //TODO clamp the float throttle coming from user input to -1 and 1 so player cant go faster by changing those values.
	auto ForceApplied = Throttle * GetForwardVector() * MaxDrivingForce; // V = (user input between -1 and 1) * this mex X vector * F in Newtons./ V = (user input between -1 and 1) * this mex X vector * F in Newtons.
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());//we need to cast the root component to UPrimitive component because
	//we cant add force to USceneComponent parent of primitive component parent of Static mesh component.
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	// auto ForceApplied = Throttle * GetForwardVector() * MaxDrivingForce;
	// AddImpulse(ForceApplied,EName::None, true);
}
