// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankTurret.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward Declaration
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelSetter);
	void SetTurretReference(UTankTurret* TurretSetter);

public:
	//Aim At Hit Location That we declared in TankPlayer controller by ray casting throw aim UI to world with a max range.
	void AimAt(FVector HitLocation, float ProjectileSpeed);

private:
	//Will be set in my cpp with the barrel fbx sent throw blueprint via Tank C++ class and barrel has his own c++ class
	//so we will use UTankBarrel Instead of UStaticMesh component.
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
