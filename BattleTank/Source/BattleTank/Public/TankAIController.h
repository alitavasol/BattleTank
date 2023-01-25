// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;
	
	//ATank* GetAIPossesdTank() const;
	// ATank* GetPlayerTank() const;
	APawn* MyAITank = nullptr;
	APawn* PlayerTank = nullptr;
	
	FVector MainTankLocation;

	float AcceptanceRadius = 3000;
public:
	virtual void Tick(float DeltaSeconds) override;
};
