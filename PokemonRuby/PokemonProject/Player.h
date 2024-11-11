#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>
#include "PokemonMath.h"

class APlayer : public AActor
{
public:
    enum class APlayerState
    {
        
        IDLE,
        WALK,
        RUN,
        JUMP,
    };

    enum class EPlayerDir
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        MAX
    };


    // constrcuter destructer
    APlayer();
    ~APlayer();

    // delete Function
    APlayer(const APlayer& _Other) = delete;
    APlayer(APlayer&& _Other) noexcept = delete;
    APlayer& operator=(const APlayer& _Other) = delete;
    APlayer& operator=(APlayer&& _Other) noexcept = delete;

    void BeginPlay() override;
    void Tick(float _DeltaTime) override;
    void PlayerCameraCheck();
    void PlayerDebugCheck(float _DeltaTime);
    void MapSizeCheck(FVector2D _Size);

    void SetObject();

    void LevelChangeStart();
    void LevelChangeEnd();
    
    void Idle(float _DeltaTime);
    void Walk(float _DeltaTime);
    void ChangeState(APlayerState _CurPlayerState);
    void IdleStart();
    void WalkStart();
    void StartMoveAndAnimation();
    void OnMoveComplete();
    void OnAnimationComplete();

    int RoundToInt(float Value);
    
    FVector2D GetTargetLocation() const;
    void SetTargetLocation(const FVector2D& NewTarget);
    FVector2D SnapToTileGrid(const FVector2D& Location);

    EPlayerDir GetPressDirection();
    FVector2D GetActualLocation() const 
    {
        return CurPos;
    }



protected:

private:
   float WalkSpeed = 96;
   APlayerState CurPlayerState = APlayerState::IDLE;


    bool bIsMoving = false;           // 이동 중인지 여부
    FVector2D TargetLocation = FVector2D::ZERO; // 목표 위치
    EPlayerDir CurDir = EPlayerDir::DOWN;
    FVector2D CurPos;


    float MoveTimeElapsed;    // 이동 시간이 경과한 시간
    float AnimationTimeElapsed; // 애니메이션 시간이 경과한 시간

    bool bMoveTimerActive;    // 이동 타이머 활성화 여부
    bool bAnimationTimerActive; // 애니메이션 타이머 활성화 여부

    float WalkTime = 2.0f;    // 한 칸 이동하는 데 걸리는 시간 (2초)
    float AnimationTime = 3.0f; // 애니메이션이 지속되는 시간 (3초)


    bool bCanChangeDirection = true;  // 방향 전환 가능 여부
    float DirectionChangeDelayTime = 0.1f; // 방향 전환을 위한 딜레이 시간 (초)
    float DirectionChangeTimer = 0.0f; // 딜레이 타이머

  


    FVector2D MapSize = FVector2D::ZERO;

    class USpriteRenderer* SpriteRenderer = nullptr;
    class USpriteRenderer* SpriteMapRenderer = nullptr;

    UFSMStateManager FSM;

};

