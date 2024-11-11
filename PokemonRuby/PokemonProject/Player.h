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

    

    
    FVector2D GetTargetLocation() const;
    void SetTargetLocation(const FVector2D& NewTarget);

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



    FVector2D MapSize = FVector2D::ZERO;

    class USpriteRenderer* SpriteRenderer = nullptr;
    class USpriteRenderer* SpriteMapRenderer = nullptr;

    UFSMStateManager FSM;
};

