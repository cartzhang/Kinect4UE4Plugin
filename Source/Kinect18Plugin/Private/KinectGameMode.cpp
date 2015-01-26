// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

//#include "KNTest2.h"
#include "Kinect18PrivatePCH.h"
#include "KinectGameMode.h"
#include "KinectPawn.h"
#include "KinectPlayerController.h"


AKinectGameMode::AKinectGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// set default PlayerController class to our Blueprinted character
	PlayerControllerClass = AKinectPlayerController::StaticClass();
	//DefaultPawnClass = AKinectPawn::StaticClass();
}

void AKinectGameMode::Tick(float DeltaSeconds)
{
	FString jsEvent = FString::Printf(TEXT("var event = new CustomEvent(\"game.tick\", {detail: {deltaTime : %0.4f}}); Object.dispatchEvent(event);"), DeltaSeconds);
	
	//if (Flathead::IsAvailable())
	//{
	//	Flathead::Get().Execute(jsEvent, TEXT("GameMode"));
	//}
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Welcom to Kincet  WORLD"));
	}
}

void AKinectGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}

void AKinectGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	//const int32 BotsCountOptionValue = GetIntOption(Options, GetBotsCountOptionName(), 0);
	//SetAllowBots(BotsCountOptionValue > 0 ? true : false, BotsCountOptionValue);
	Super::InitGame(MapName, Options, ErrorMessage);

}

AActor* AKinectGameMode::ChoosePlayerStart(AController* Player)
{
	return Super::ChoosePlayerStart(Player);
}

void AKinectGameMode::PreLogin(const FString& Options, const FString& Address, const TSharedPtr<class FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	AGameState* const MyGameState = GameState;
	const bool bMatchIsOver = MyGameState && MyGameState->HasMatchEnded();
	if (bMatchIsOver)
	{
		ErrorMessage = TEXT("Match is over!");
	}
	else
	{
		// GameSession can be NULL if the match is over
		Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	}
}

