// Copyright 2012-2015. All Rights Reserved.
#pragma once
#include "KinectPlayerController.generated.h"

UENUM(BlueprintType)
enum class EkinectBoneEnum : uint8
{
	VE_Dance 	UMETA(DisplayName = "Dance"),
	VE_Rain 	UMETA(DisplayName = "Rain"),
	VE_Song	UMETA(DisplayName = "Song")
};

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableEvent_PickupRespawned, AKinectPlayerController*);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_PickupPickedup, AKinectPlayerController*);

UCLASS(config=Game)
class AKinectPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableEvent_PickupPickedup, AKinectPlayerController*, OnPickupRespawnedDelegate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Kinect18)
	bool bChangeMapFrame;
public:
	/** sets spectator location and rotation */
	UFUNCTION(reliable, client)
	void ClientSetSpectatorCamera(FVector CameraLocation, FRotator CameraRotation);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "K4U Start Game"))
	virtual void K4UStartGame();

	/** Called when pickup is picked up */
	UPROPERTY(BlueprintAssignable, Category = Kinect18)
	FBindableEvent_PickupPickedup OnPickupPickedupDelegate;

	/** Called when pickup respawns */
	UPROPERTY(BlueprintAssignable, Category = Kinect18)
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

	virtual void BeginPlay() override;

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
	// 记录手势当前位置
	enum GesturePos{
		NonePos = 0,
		Left,
		Right,
		Neutral
	};

	// 判断识别状态
	enum DetectionState{
		NoneState = 0,
		Success,
		Failed,
		InProgress
	};

	// 判断手势需要的数据
	struct DataState{
		GesturePos Pos;		// 每个人的左右手
		DetectionState State;
		int times;
		time_t timestamp;
		void Reset()
		{
			Pos = GesturePos::NonePos;
			State = DetectionState::NoneState;
			times = 0;
			timestamp = 0;
		}
	};

	//int32 CheckGeture();
	//DataState WaveDatas[NUI_SKELETON_COUNT][2];		// 记录每个人，每只手的状态
	int LeftHand;							// 左手 ID
	int RightHand;							// 右手 ID
	// 中间位置阀值：在该范围内的都认为手在中间位置（相对于肘部的 x 坐标）
	float NeutralThreshold;
	// 挥手次数阀值，达到该次数认为是挥手
	int Times;
	// 时间限制，如果超过该时间差依然识别不出挥手动作则认为识别失败
	double Difftimes;

	void InitGesture(float NeutralThreshold, int Times, double Difftimes);

	bool IsLeftSide(float curpos, float center)
	{
		return curpos < (center - NeutralThreshold);
	}
	bool IsRightSide(float curpos, float center)
	{
		return curpos >(center + NeutralThreshold);
	}
	bool IsNeutral(float curpos, float center)
	{
		return !IsLeftSide(curpos, center) && !IsRightSide(curpos, center);
	}
	//// 判断骨骼追踪情况：包括骨骼追踪完好且手部位置在肘上面
	//bool IsSkeletonTrackedWell(const NUI_SKELETON_DATA& skeletonData,bool isLeft = true)
	//{
	//	int elbow = (isLeft) ? NUI_SKELETON_POSITION_ELBOW_LEFT :
	//		NUI_SKELETON_POSITION_ELBOW_RIGHT;

	//	int hand = (isLeft) ? NUI_SKELETON_POSITION_HAND_LEFT :
	//		NUI_SKELETON_POSITION_HAND_RIGHT;

	//	if (skeletonData.eTrackingState != NUI_SKELETON_NOT_TRACKED)
	//	{
	//		if ((skeletonData.eSkeletonPositionTrackingState[hand]
	//			!= NUI_SKELETON_POSITION_NOT_TRACKED)
	//			&& (skeletonData.eSkeletonPositionTrackingState[elbow]
	//			!= NUI_SKELETON_POSITION_NOT_TRACKED))
	//		{
	//			if (skeletonData.SkeletonPositions[hand].y > skeletonData.SkeletonPositions[elbow].y)
	//				return true;
	//		}
	//	}
	//	return false;
	//}

	void JudgeGesture();
private:
	int TempTimes;
};

