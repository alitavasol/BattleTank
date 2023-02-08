// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum EFiringState
{
	Reloading,
	MovingBarrel,
	ReadyToFire
};

//Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=("Custom"), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// void SetBarrelReference(UTankBarrel* BarrelSetter);
	// void SetTurretReference(UTankTurret* TurretSetter);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* GiveMeBarrelFromBP, UTankTurret* GiveMeTurretFromBP);
	
	//Aim At Hit Location That we declared in TankPlayer controller by ray casting throw aim UI to world with a max range.
	void AimAt(FVector HitLocation) ;

private:
	//Will be set in my cpp with the barrel fbx sent throw blueprint via Tank C++ class and barrel has his own c++ class
	//so we will use UTankBarrel Instead of UStaticMesh component.
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	double LastTimeFired = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Fire Setup", meta = (AllowPrivateAccess = true))
	float ProjectileSpeed = 50000; //0.5 km per second is the speed of projectile and can be changed.
	UPROPERTY(EditDefaultsOnly, Category = "Fire Setup", meta = (AllowPrivateAccess = true))
	float RelaodCD = 3;
	
	void MoveBarrelTowards();

protected:
	UPROPERTY(BlueprintReadOnly, category = "FiringState")
	TEnumAsByte<EFiringState> FiringState = Reloading;

	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();

	//Read only enum firing state getter.
	EFiringState FireStateGetter() const;
private:
	bool IsBarrelMoving();
	FVector AimDirection;
};
