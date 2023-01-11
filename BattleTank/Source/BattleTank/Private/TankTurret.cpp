// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RotateRightOrLeft)
{
	FMath::Clamp<float>(RotateRightOrLeft, -1, 1);
	auto RotateLeftorRightWithCertainSpeed = RotateRightOrLeft * SpeedOFTurretRotating * GetWorld()->DeltaTimeSeconds;
	auto TurretNewRotation = this->GetRelativeRotation().Yaw + RotateLeftorRightWithCertainSpeed;

	this->SetRelativeRotation(FRotator(0, TurretNewRotation,0));
}
