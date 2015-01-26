// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "KinectGameMode.generated.h"

UCLASS(minimalapi)
class AKinectGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual void StartPlay() override;
public:

	/** Initialize the game. This is called before actors' PreInitializeComponents. */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	/** select best spawn point for player */
	virtual AActor* ChoosePlayerStart(AController* Player) override;

	/** Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string. */
	virtual void PreLogin(const FString& Options, const FString& Address, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage) override;

};

