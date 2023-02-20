// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	MyAITank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if(!ensure(PossessedTank)) { return; }
		//subscribe our local method to Tank Death Event.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Recieved Death Event"));
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(PlayerTank && MyAITank)){ return; }
	//Move To main player tank
	MoveToActor(PlayerTank,AcceptanceRadius);
		
	MainTankLocation = PlayerTank->GetActorLocation();
	AimingComponent->AimAt(MainTankLocation);
	if (AimingComponent->FireStateGetter() == ReadyToFire)// EFiringState::ReadyToFire
	{
		AimingComponent->Fire();
	}
}
