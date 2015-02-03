// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Kinect18PrivatePCH.h"
#include "KinectProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AKinectProjectile::AKinectProjectile(const class FPostConstructInitializeProperties& PCIP) 
	: Super(PCIP)
{
	// Use a sphere as a simple collision representation
	CollisionComp = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");			// Collision profiles are defined in DefaultEngine.ini
	CollisionComp->OnComponentHit.AddDynamic(this, &AKinectProjectile::OnHit);		// set up a notification for when this component hits something blocking
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AKinectProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}