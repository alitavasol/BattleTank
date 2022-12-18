// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto const TankPawn = GetPlayerTank();
	if (TankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player 0 found by AI, Player 0  id = %s"), *(TankPawn->GetName()));
	}
	if (!TankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could NOT find Player 0 (Player 0 = null)"));
	}
}

ATank* ATankAIController::GetAIPossesdTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	if (auto const Player0TankPawn = GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		return Cast<ATank>(Player0TankPawn);	
	}
	else
	{
	return nullptr;	
	}
}
