// Copyright 2012-2015. All Rights Reserved.
#pragma once
#include "KinectPlayerController.generated.h"

UCLASS(config=Game)
class AKinectPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableEvent_PickupPickedup, AKinectPlayerController*, OnPickupRespawnedDelegate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KINECTUE)
	bool bChangeMapFrame;
public:
	/** sets spectator location and rotation */
	UFUNCTION(reliable, client)
	void ClientSetSpectatorCamera(FVector CameraLocation, FRotator CameraRotation);
	
	/** Called when pickup is picked up */
	UPROPERTY(BlueprintAssignable, Category = KINECTUE)
	FBindableEvent_PickupPickedup OnPickupPickedupDelegate;

	/** Called when pickup respawns */
	UPROPERTY(BlueprintAssignable, Category = KINECTUE)
	FBindableEvent_PickupPickedup OnPickupRespawnedDelegate;

protected:
	/** true for the first frame after the game has ended */
	uint8 bGameEndedFrame : 1;

	/** stores pawn location at last player death, used where player scores a kill after they died **/
	FVector LastDeathLocation;
protected:

	/** try to find spot for death cam */
	bool FindDeathCameraSpot(FVector& CameraLocation, FRotator& CameraRotation);

	//Begin AActor interface

	/** after all game elements are created */
	virtual void PostInitializeComponents() override;

	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	//End AActor interface
	//Begin AController interface

	/** transition to dead state, retries spawning later */
	virtual void FailedToSpawnPawn() override;

	/** update camera when pawn dies */
	virtual void PawnPendingDestroy(APawn* P) override;

	//End AController interface
	// Begin APlayerController interface

	/** respawn after dying */
	virtual void UnFreeze() override;

	/** sets up input */
	virtual void SetupInputComponent() override;

	/**
	* Called from game info upon end of the game, used to transition to proper state.
	*
	* @param EndGameFocus Actor to set as the view target on end game
	* @param bIsWinner true if this controller is on winning team
	*/
	virtual void GameHasEnded(class AActor* EndGameFocus = NULL, bool bIsWinner = false) override;
public:
};

