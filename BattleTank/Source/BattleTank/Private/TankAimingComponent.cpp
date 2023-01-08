// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

#include "Tank.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
//This Will be called from Tank.cpp and pass the barrel static mesh from bluePrint to us
void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelSetter)
{
	Barrel = BarrelSetter;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//Aim At hit location pass throw tank player controller or AI Controller (if player controller then its land scape locations and if AI is possessing this tank then its the player main tank location)
void UTankAimingComponent::AimAt(FVector HitLocation) const
{
	auto BarrelLocation =  Barrel->GetComponentLocation();
	const FString OurTankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Is Aiming At %s From Tip of the barrel located at %s"), *OurTankName, *HitLocation.ToString(),*BarrelLocation.ToString());
}


