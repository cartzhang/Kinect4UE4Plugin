// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Kinect18PrivatePCH.h"
#include "KinectPlayerCharacter.h"
#include "KinectProjectile.h"
#include "Animation/AnimInstance.h"

#include "Engine.h"
#include "AllowWindowsPlatformTypes.h"
#include "UDKinect.h"
//#include "NuiSensor.h"
using namespace  UDKinect;
#include "HideWindowsPlatformTypes.h"

//////////////////////////////////////////////////////////////////////////
// AU4UE4TestCharacter
#define  USER_INDEX   0

AKinectPlayerCharacter::AKinectPlayerCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AKinectPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	InputComponent->BindAction("Fire", IE_Pressed, this, &AKinectPlayerCharacter::OnFire);
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AKinectPlayerCharacter::TouchStarted);

	InputComponent->BindAxis("MoveForward", this, &AKinectPlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AKinectPlayerCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AKinectPlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AKinectPlayerCharacter::LookUpAtRate);
}

void AKinectPlayerCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AKinectProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if(FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if(AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void AKinectPlayerCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// only fire for first finger down
	if (FingerIndex == 0)
	{
		OnFire();
	}
}

void AKinectPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AKinectPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AKinectPlayerCharacter::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorUpVector(), Value);
	}
}
void AKinectPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AKinectPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AKinectPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//
	JudgeGesture();
}

void AKinectPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UDKinectInitialize(eUserTrackingStyle_QUEUE, eSkeletonSmoothing_FAST_LOW_LATENCY);
	UDKinectShowPreviewWindows();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Welcom to Kincet  WORLD"));
	}

}

void AKinectPlayerCharacter::BeginDestroy()
{
	UDKinectShutDown();
	UDKinectHidePreviewWindows();
	Super::BeginDestroy();
}

FVector AKinectPlayerCharacter::GetJoinTypeRightHandPostion(int32 NameID)
{
	FVector FvResult = FVector::ZeroVector;	
	UDKinect::UDKVector pBonePosition;
	pBonePosition.x = pBonePosition.y = pBonePosition.z = 0.0f;

	UDKinectGetSkeletonPosition(USER_INDEX, NUI_SKELETON_POSITION_HAND_RIGHT, &pBonePosition);	
	FvResult = FVector(pBonePosition.x, pBonePosition.y, pBonePosition.z);
	return FvResult;
}

FVector AKinectPlayerCharacter::GetJoinTypeLeftHandPostion(int32 NameID)
{
	FVector FvResult = FVector::ZeroVector;
	UDKinect::UDKVector pBonePosition;
	pBonePosition.x = pBonePosition.y = pBonePosition.z = 0.0f;

	UDKinectGetSkeletonPosition(USER_INDEX, NUI_SKELETON_POSITION_HAND_LEFT, &pBonePosition);
	FvResult = FVector(pBonePosition.x, pBonePosition.y, pBonePosition.z);
	return FvResult;
}


void AKinectPlayerCharacter::JudgeGesture()
{
	int UserId = 0;
	int ShoulderBoneId = NUI_SKELETON_POSITION_SHOULDER_CENTER;
	if (UDKinectGetSkeletonTrackingState(UserId, ShoulderBoneId) <= 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Could not track the object!"));
		}
		return;
	}

	UDKinect::UDKVector pShoulderBonePosition;
	pShoulderBonePosition.x = 0;
	UDKinectGetSkeletonPosition(UserId, ShoulderBoneId, &pShoulderBonePosition);

	int SpineBoneId = NUI_SKELETON_POSITION_SPINE;
	UDKinect::UDKVector pSpineBonePosition;
	pSpineBonePosition.x = pSpineBonePosition.y = pSpineBonePosition.z = 0;
	UDKinectGetSkeletonPosition(UserId, SpineBoneId, &pSpineBonePosition);

	float delt = pShoulderBonePosition.x - pSpineBonePosition.x;
	if (delt >= 0.06)
	{
		MoveRight(1.0f);
	}
	else if (delt <= -0.06)
	{
		MoveRight(-1.0f);
	}
}
