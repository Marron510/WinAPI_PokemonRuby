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
        LEFT_Left_Arm,
        LEFT_Right_Arm,
        RIGHT_Left_Arm,
        RIGHT_Right_Arm,
        UP_Left_Arm,
        UP_Right_Arm,
        DOWN_Left_Arm,
        DOWN_Right_Arm,
        MAX
    };

    std::unordered_map<EPlayerDir, int> DirectionMoveCount = {
       { EPlayerDir::UP_Left_Arm, 0 },
       { EPlayerDir::UP_Right_Arm, 0 },
       { EPlayerDir::LEFT_Left_Arm, 0 },
       { EPlayerDir::LEFT_Right_Arm, 0 },
       { EPlayerDir::DOWN_Left_Arm, 0 },
       { EPlayerDir::DOWN_Right_Arm, 0 },
       { EPlayerDir::RIGHT_Left_Arm, 0 },
       { EPlayerDir::RIGHT_Right_Arm, 0 }
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
    void SetColImage(std::string_view _ColImageName);
    void SetTargetLocation(const FVector2D& NewTarget);
    void SetDirection(EPlayerDir NewDirection);

    void LevelChangeStart();
    void LevelChangeEnd();

    void Idle(float _DeltaTime);
    void Walk(float _DeltaTime);
    void ChangeState(APlayerState _CurPlayerState);
    void IdleStart();
    void HandleInput();
    void StartMovement(EPlayerDir Direction, FVector2D Offset);
    void UpdateMovement(float _DeltaTime);
    void ChangeArmAnimation();
    void MoveToTile(const FVector2D& TargetTile);

    void InitializeSprites();
    void InitializeAnimations();
    void StartMovementWithAnimation(EPlayerDir LeftArmDir, EPlayerDir RightArmDir, FVector2D Offset);

    void HandleBattleEncounter();

    FVector2D GetTargetLocation() const;
    EPlayerDir GetPressDirection();
    EPlayerDir GetArmDirection(EPlayerDir LeftArmDir, EPlayerDir RightArmDir);
    EPlayerDir GetCurDir()
    {
        return CurDir;
    }
    

    void IncArmOrder()
    {
        ArmOrder = (ArmOrder + 1) % 2; 
    }

    FVector2D GetCamPos() const
    {
        return CamPos;
    }
    
    USpriteRenderer* GetPlayerRender()
    {
        return SpriteRenderer;
    }

protected:

private:
    float WalkSpeed = 0.24;
    float WalkTime = 0.0f;
    const float TileMoveTime = 1.6f;
    
    bool IsMoving = false;
    bool bIsLeftArm = true;


    EPlayerDir CurDir = EPlayerDir::DOWN_Left_Arm;
    APlayerState CurPlayerState = APlayerState::IDLE;

    FVector2D TargetLocation = FVector2D::ZERO;
    FVector2D CurrentDirection = FVector2D::ZERO;

    class USpriteRenderer* SpriteRenderer = nullptr;
    class USpriteRenderer* SpriteMapRenderer = nullptr;
    class UEngineWinImage* ColImage = nullptr;
    class UEngineWinImage* MotherColImage = nullptr;
    FVector2D MapSize = FVector2D::ZERO;
    UColor CheckColor = UColor::WHITE;

    UFSMStateManager FSM;
    
    FVector2D TileSize = FVector2D(96, 96);

    int ArmOrder = 0; // 0: ¿ÞÆÈ, 1: ¿À¸¥ÆÈ

    int MoveCount = 0;
    bool bCanProcessInput = true; 
    float InputCooldown = 0.0f;   

    FVector2D CamPos = FVector2D::ZERO;
};