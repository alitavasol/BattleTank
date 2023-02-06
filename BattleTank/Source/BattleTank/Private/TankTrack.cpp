// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	TankRootAsStaticMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}


void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!ensure(TankRootAsStaticMesh)) { return; }
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if we slipping side way then slippage speed is 1 and 0 if we are going straight.
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
	//The Acceleration In This Frame We need in F = ma To Correct.
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	//Force To Apply Side Ways F = ma
	auto CorrectionForce = (TankRootAsStaticMesh->GetMass() * CorrectionAcceleration) / 2;// 2 Tracks, crashes If not Divided By 2
	//Add Force
	TankRootAsStaticMesh->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// //TODO clamp the float throttle coming from user input to -1 and 1 so player cant go faster by changing those values.
	auto ForceApplied = Throttle * GetForwardVector().GetSafeNormal() * MaxDrivingForce; // V = (user input between -1 and 1) * this mex X vector * F in Newtons./ V = (user input between -1 and 1) * this mex X vector * F in Newtons.
	auto ForceLocation = GetComponentLocation();
	//auto TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());//we need to cast the root component to UPrimitive component because
	//we cant add force to USceneComponent parent of primitive component parent of Static mesh component.
	TankRootAsStaticMesh->AddForceAtLocation(ForceApplied, ForceLocation);
	// auto ForceApplied = Throttle * GetForwardVector() * MaxDrivingForce;
	// AddImpulse(ForceApplied,EName::None, true);
}
