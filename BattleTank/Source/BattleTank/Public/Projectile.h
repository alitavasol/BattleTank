// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void LaunchProjectile(float Speed);

private:
	void OnTimerExpireDelegate();
	
	UProjectileMovementComponent* PtrToProjectileMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	float DestroyDelay = 10.0f;
	
	//On Component Hit Event.
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
