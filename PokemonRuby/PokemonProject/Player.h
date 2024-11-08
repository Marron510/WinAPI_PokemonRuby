#pragma once
#include <EngineCore/Actor.h>
#include "PokemonMath.h"

class APlayer : public AActor
{
public:
    enum class APlayerState
    {
        NONE,
        IDLE,
        WALK,
        RUN,
        JUMP,
    };

    enum class APlayerDir
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
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

    void LevelChangeStart();
    void LevelChangeEnd();
    void SetObject(FVector2D _location);
    FTileVector SetActorTileLocation(FTileVector _CurPos);

    void StateUpdate(float _DeltaTime);

    void ChangeAnimation(APlayerState _State, FTileVector _Direction);
    void StateChange(APlayerState _State, bool _Restart = false);



    void Idle(float _DeltaTime);
    void Walk(float _DeltaTime);
    void IdleStart();
    void WalkStart();




protected:

private:
    float WalkSpeed = 3.0f;
    float WalkTime = 1.0f / WalkSpeed;
    float CurWalkTime = WalkTime;
    float WalkInputLatency = 0.75f;
    float RotateTime = 0.5f / WalkSpeed;
    float CurRotateTime = RotateTime;

    bool IsRotate = false;
    bool IsExecutingMovingLogic = false;

    APlayerState CurPlayerState = APlayerState::IDLE;

    FTileVector Direction = FTileVector::Down;
    FTileVector PrevPos;
    FTileVector CurPos;
    FTileVector NextPos;


    int MySpriteIndex = 0;
    FVector2D MapSize = FVector2D::ZERO;

    class USpriteRenderer* SpriteRenderer = nullptr;
    class USpriteRenderer* SpriteMapRenderer = nullptr;


    UFSMStateManager FSM;
};

