// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* GiveMeBarrelFromBP, UTankTurret* GiveMeTurretFromBP)
{
	Barrel = GiveMeBarrelFromBP;
	Turret = GiveMeTurretFromBP;
}

//This Will be called from Tank.cpp and pass the barrel static mesh from bluePrint to us
// void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelSetter)
// {
// 	Barrel = BarrelSetter;
// 	if (BarrelSetter == nullptr)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("BarrelSetter == Nullptr"))
// 		return;
// 	}
// }

// void UTankAimingComponent::SetTurretReference(UTankTurret* TurretSetter)
// {
// 	if (TurretSetter == nullptr)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("TurretSetter == Nullptr"))
// 		return;
// 	}
// 	Turret = TurretSetter;
// }

//Aim At hit location pass throw tank player controller or AI Controller (if player controller then its land scape locations
//and if AI is possessing this tank then its the player main tank location)
void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileSpeed)
{
	//protecting pointer
	if (Barrel == nullptr|| !Turret){ return; }
	//calculating an launch velocity for a projectile to hit our hit location point.
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileLauncher"));//Start location of projectile is the tip of the barrel.
	FVector SuggestedOutTossVelocityByEngine;//Output velocity of SuggestProjectileVelocity Method.
	//If Succeeded To return the toss velocity then do the things we desire.

	//Engine Will Suggest us toss velocity with this method.
	bool CouldCalculateTossVelosity = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		SuggestedOutTossVelocityByEngine,
		StartLocation,HitLocation,
		ProjectileSpeed,false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if(CouldCalculateTossVelosity == true)
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//if we normalize the toss velocity that engine gave us we can calculate the Aim Direction.
		auto AimDirection = SuggestedOutTossVelocityByEngine.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work-out deference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimDirectionConvertedToRotation = AimDirection.Rotation();
	auto DELTARotation = AimDirectionConvertedToRotation - BarrelRotation;//delta R = R2 - R1;

	Barrel->ElevateBarrel(DELTARotation.Pitch);
	Turret->RotateTurret(DELTARotation.Yaw);
}


