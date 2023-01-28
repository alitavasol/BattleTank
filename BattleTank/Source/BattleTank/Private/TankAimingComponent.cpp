// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastTimeFired = GetWorld()->TimeSeconds;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((GetWorld()->TimeSeconds - LastTimeFired) < RelaodCD)
	{
		FiringState = EFiringState::Reloading;
		UE_LOG(LogTemp, Warning, TEXT("Reloading"))
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::MovingBarrel;
		UE_LOG(LogTemp, Warning, TEXT("Moving Barrel"))
	}
	else
	{
		FiringState = EFiringState::ReadyToFire;
		UE_LOG(LogTemp, Warning, TEXT("Ready To Fire"))
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* GiveMeBarrelFromBP, UTankTurret* GiveMeTurretFromBP)
{
	Barrel = GiveMeBarrelFromBP;
	Turret = GiveMeTurretFromBP;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//protecting pointer
	if (!ensure(Barrel || Turret)){ return; }
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
		//if we normalize the toss velocity that engine gave us we can calculate the Aim Direction.
		AimDirection = SuggestedOutTossVelocityByEngine.GetSafeNormal();
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::MoveBarrelTowards()
{
	//Work-out deference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimDirectionConvertedToRotation = AimDirection.Rotation();
	auto DELTARotation = AimDirectionConvertedToRotation - BarrelRotation;//delta R = R2 - R1;

	Barrel->ElevateBarrel(DELTARotation.Pitch);
	Turret->RotateTurret(DELTARotation.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading )
	{
		if(!ensure(Barrel && ProjectileBlueprint)) { return; }
		auto SpawnLocation = Barrel->GetSocketLocation(FName("ProjectileLauncher"));
		auto SpawnRotation = Barrel->GetSocketRotation(FName("ProjectileLauncher"));
		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);
		SpawnedProjectile->LaunchProjectile(ProjectileSpeed);
		LastTimeFired = GetWorld()->TimeSeconds;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if(!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	if (BarrelForward.Equals(AimDirection, 0.1))
	{
		return false;
	}
	return true;
}




