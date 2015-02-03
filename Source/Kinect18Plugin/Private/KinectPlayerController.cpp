// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Kinect18PrivatePCH.h"
#include "KinectPlayerController.h"
//#include "Actor.h"
//#include "AllowWindowsPlatformTypes.h"
//#include "UDKinect.h"
//#include "NuiSensor.h"
//using namespace  UDKinect;
//#include "HideWindowsPlatformTypes.h"

AKinectPlayerController::AKinectPlayerController(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
{
	bGameEndedFrame = false;
	LastDeathLocation = FVector::ZeroVector;
}

void AKinectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI input	
	//InputComponent->BindAction("Scoreboard", IE_Pressed, this, &AKinectPlayerController::OnShowScoreboard);
}

void AKinectPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AKinectPlayerController::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
	
	// Is this the first frame after the game has ended
	if (bGameEndedFrame)
	{
		bGameEndedFrame = false;
		// ONLY PUT CODE HERE WHICH YOU DON'T WANT TO BE DONE DUE TO HOST LOSS
		// Do we need to show the end of round scoreboard?
		if (IsPrimaryPlayer())
		{
			bChangeMapFrame = true;
		}
	}
};

void AKinectPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AKinectPlayerController::FailedToSpawnPawn()
{
	if (StateName == NAME_Inactive)
	{
		BeginInactiveState();
	}
	Super::FailedToSpawnPawn();
}

void AKinectPlayerController::PawnPendingDestroy(APawn* P)
{
	LastDeathLocation = P->GetActorLocation();
	FVector CameraLocation = LastDeathLocation + FVector(0, 0, 300.0f);
	FRotator CameraRotation(-90.0f, 0.0f, 0.0f);
	FindDeathCameraSpot(CameraLocation, CameraRotation);

	Super::PawnPendingDestroy(P);

	ClientSetSpectatorCamera(CameraLocation, CameraRotation);
}

void AKinectPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	// write stats
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	Super::GameHasEnded(EndGameFocus, bIsWinner);
}

bool AKinectPlayerController::FindDeathCameraSpot(FVector& CameraLocation, FRotator& CameraRotation)
{

	const FVector PawnLocation = GetPawn()->GetActorLocation();
	FRotator ViewDir = GetControlRotation();
	ViewDir.Pitch = -45.0f;

	const float YawOffsets[] = { 0.0f, -180.0f, 90.0f, -90.0f, 45.0f, -45.0f, 135.0f, -135.0f };
	const float CameraOffset = 600.0f;
	FCollisionQueryParams TraceParams(TEXT("DeathCamera"), true, GetPawn());

	for (int32 i = 0; i < ARRAY_COUNT(YawOffsets); i++)
	{
		FRotator CameraDir = ViewDir;
		CameraDir.Yaw += YawOffsets[i];
		CameraDir.Normalize();

		const FVector TestLocation = PawnLocation - CameraDir.Vector() * CameraOffset;
		const bool bBlocked = GetWorld()->LineTraceTest(PawnLocation, TestLocation, ECC_Camera, TraceParams);

		if (!bBlocked)
		{
			CameraLocation = TestLocation;
			CameraRotation = CameraDir;
			return true;
		}
	}

	return false;
}

void AKinectPlayerController::ClientSetSpectatorCamera_Implementation(FVector CameraLocation, FRotator CameraRotation)
{
	SetInitialLocationAndRotation(CameraLocation, CameraRotation);
	SetViewTarget(this);
}

