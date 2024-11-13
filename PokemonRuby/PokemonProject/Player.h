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
    void PlayerGroundCheck(FVector2D _MovePos);

    void SetObject();

    void LevelChangeStart();
    void LevelChangeEnd();

    void Idle(float _DeltaTime);
    void Walk(float _DeltaTime);
    void ChangeState(APlayerState _CurPlayerState);
    void IdleStart();
    void WalkStart();



    EPlayerDir GetCurDir()
    {
        return CurDir;
    }

    void SetColImage(std::string_view _ColImageName);
    FVector2D GetTargetLocation() const;
    void SetTargetLocation(const FVector2D& NewTarget);

    EPlayerDir GetPressDirection();

    
   
protected:

private:
    float WalkSpeed = 0.96;
    float WalkTime = 0.0f;
    bool IsMoving = false;
    const float TileMoveTime = 2.4f;
    
    EPlayerDir CurDir = EPlayerDir::DOWN;
    APlayerState CurPlayerState = APlayerState::IDLE;

    FVector2D TargetLocation = FVector2D::ZERO;
    FVector2D CurrentDirection = FVector2D::ZERO;

    class USpriteRenderer* SpriteRenderer = nullptr;
    class USpriteRenderer* SpriteMapRenderer = nullptr;
    class UEngineWinImage* ColImage = nullptr;
    FVector2D MapSize = FVector2D::ZERO;
    UColor CheckColor = UColor::WHITE;

    UFSMStateManager FSM;
    
    FVector2D TileSize = FVector2D(96, 96);
};

