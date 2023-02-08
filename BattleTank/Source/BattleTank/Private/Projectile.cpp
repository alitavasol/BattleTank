// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PtrToProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	PtrToProjectileMovementComponent->bAutoActivate = false;
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	RootComponent = CollisionMesh;
	CollisionMesh->SetNotifyRigidBodyCollision(true);//Simulation Generates Hit Box Will Be Set to true By default.
	CollisionMesh->SetVisibility(false);
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(CollisionMesh,FAttachmentTransformRules::KeepRelativeTransform,NAME_None);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//projectile launcher
void AProjectile::LaunchProjectile(float Speed)
{
	PtrToProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	PtrToProjectileMovementComponent->Activate();
}


