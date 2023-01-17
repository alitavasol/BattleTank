// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s : Throttle :%f"),*name, Throttle)
	//TODO clamp the float throttle coming from user input to -1 and 1 so player cant go faster by changing those values.
}