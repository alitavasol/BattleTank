// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	TankRootAsStaticMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>((CurrentThrottle + Throttle), -1 , 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = CurrentThrottle * GetForwardVector().GetSafeNormal() * MaxDrivingForce; // V = (user input between -1 and 1) * this mex X vector * F in Newtons./ V = (user input between -1 and 1) * this mex X vector * F in Newtons.
	auto ForceLocation = GetComponentLocation();
	//auto TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());//we need to cast the root component to UPrimitive component because
	//we cant add force to USceneComponent parent of primitive component parent of Static mesh component.
	TankRootAsStaticMesh->AddForceAtLocation(ForceApplied, ForceLocation);
	// auto ForceApplied = Throttle * GetForwardVector() * MaxDrivingForce;
	// AddImpulse(ForceApplied,EName::None, true);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySideWaysForce();
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySideWaysForce()
{
	//if we slipping side way then slippage speed is 1 and 0 if we are going straight.
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
	//The Acceleration In This Frame We need in F = ma To Correct.
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	//Force To Apply Side Ways F = ma
	auto CorrectionForce = (TankRootAsStaticMesh->GetMass() * CorrectionAcceleration) / 2;// 2 Tracks, crashes If not Divided By 2
	//Add Force
	TankRootAsStaticMesh->AddForce(CorrectionForce);
}
