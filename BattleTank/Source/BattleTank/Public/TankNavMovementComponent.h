// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankTrack.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankNavMovementComponent.generated.h"

/**
 * Responsible for player tank and AI tank movement.
 */

class UTankTrack;
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float UserInput);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void TurnRight(float UserInput);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* RightTrackFromBlueprint, UTankTrack* LeftTrackFromBlueprint);
	
private:
	//called from Pathfinding logic by the ai controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;
};
