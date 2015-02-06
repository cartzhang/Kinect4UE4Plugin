// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

// Disable warning messages 4946 - reinterpret_cast of similar type
#pragma warning( push )
#pragma warning( disable : 4946 )
// Resume standard warnings
#pragma warning( pop )

#include "KinectPawn.generated.h"

UCLASS(config=Game)
class AKinectPawn : public APawn
{
public:
	GENERATED_UCLASS_BODY()

	/** StaticMesh component that will be the visuals for our flying pawn */
	//UPROPERTY(Category=Mesh, VisibleDefaultsOnly, BlueprintReadOnly)
	//TSubobjectPtr<class UStaticMeshComponent> PlaneMesh;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	TSubobjectPtr<class USpringArmComponent> SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category=Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	TSubobjectPtr<class UCameraComponent> Camera;

	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) override;
	virtual void ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// End AActor overrides

	//static void JS_UpdateImpulse(const v8::FunctionCallbackInfo<v8::Value>& args);

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override; // Allows binding actions/axes to functions
	virtual void PostInitializeComponents() override;
	// End APawn overrides

	/** Bound to the vertical axis */
	void ThrustInput(float Val);
	
	/** Bound to the horizontal axis */
	void MoveUpInput(float Val);

	/** */
	void MoveRightInput(float Val);

	void Expose();
private:

	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float Acceleration;

	/** How quickly pawn can steer */
	UPROPERTY(Category=Plane, EditAnywhere)
	float TurnSpeed;

	/** MAx forward speed */
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(Category=Yaw, EditAnywhere)
	float MinSpeed;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;
};
