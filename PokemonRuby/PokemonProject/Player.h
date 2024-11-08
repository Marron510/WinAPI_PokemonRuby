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
        NONE,
        IDLE,
        WALK,
        RUN,
        JUMP,
    };

    enum class EPlayerDir
    {
        ZERO,
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
    void SetObject();

    void LevelChangeStart();
    void LevelChangeEnd();
    
    //void PlayerGroundCheck(FVector2D _MovePos);

    /*FTileVector SetActorTileLocation(FTileVector _CurPos);

    void StateUpdate(float _DeltaTime);

    void ChangeAnimation(APlayerState _State, FTileVector _Direction);
    void StateChange(APlayerState _State, bool _Restart = false);*/



    void Idle(float _DeltaTime);
    void Walk(float _DeltaTime);
    void StateChange(APlayerState _State);
    void StateUpdate(float _DeltaTime);
    void IdleStart();
    void WalkStart();

    void CreatePlayerDirState(APlayer::EPlayerDir _Dir);

    EPlayerDir GetPressDirection();
   
protected:

private:
    float WalkSpeed = 30.0f;

    bool IsRotate = false;
    int IsGround = false;
    bool IsMove = false;

    APlayerState State;
    APlayerState CurPlayerState = APlayerState::IDLE;

    EPlayerDir CurDir = EPlayerDir::DOWN;
    FTileVector PrevPos;
    FVector2D CurPos;
    FTileVector NextPos;


    int MySpriteIndex = 0;
    FVector2D MapSize = FVector2D::ZERO;

    class USpriteRenderer* SpriteRenderer = nullptr;
    class USpriteRenderer* SpriteMapRenderer = nullptr;
    class UEngineWinImage* ColImage = nullptr;

    UFSMStateManager FSM;
};

