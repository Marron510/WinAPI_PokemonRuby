#include "PreCompile.h"
#include "MoveManager.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include "PokemonMath.h"


MoveManager::MoveManager(FVector2D& InPosition, USpriteRenderer* InSpriteRenderer)
    : Position(InPosition), SpriteRenderer(InSpriteRenderer)
{
    if (!SpriteRenderer)
    {
        MSGASSERT("SpriteRenderer는 null이 될 수 없습니다.");
    }
}



MoveManager::~MoveManager()
{
}

void MoveManager::Move(ENPCDirection Direction, float DeltaTime)
{
    FVector2D Offset;
    switch (Direction)
    {
    case ENPCDirection::UP:
        Offset = { 0.0f, -96.0f };
        break;
    case ENPCDirection::DOWN:
        Offset = { 0.0f, 96.0f };
        break;
    case ENPCDirection::LEFT:
        Offset = { -96.0f, 0.0f };
        break;
    case ENPCDirection::RIGHT:
        Offset = { 96.0f , 0.0f };
        break;
    default:
        return;
    }

    TargetLocation = Position + Offset;
    bIsMoving = true;
    UpdateAnimation(Direction);
}

void MoveManager::UpdateMovement(float DeltaTime)
{
    if (!bIsMoving) return;

    // 현재 위치와 목표 위치 비교
    if ((TargetLocation - Position).Length() < 0.1f)
    {
        Position = TargetLocation;
        bIsMoving = false;

        // SpriteRenderer 위치 갱신
        if (SpriteRenderer)
        {
            SpriteRenderer->SetComponentLocation(Position);
        }
        return;
    }

    // 위치 갱신 (Lerp를 사용하여 부드러운 이동)
    FVector2D NewLocation = UPokemonMath::Lerp(Position, TargetLocation, WalkTime / WalkSpeed);
    Position = NewLocation;

    // SpriteRenderer 위치 갱신
    if (SpriteRenderer)
    {
        SpriteRenderer->SetComponentLocation(Position);
    }
}


void MoveManager::StopMovement()
{
    bIsMoving = false;
}

void MoveManager::SetSpeed(float Speed)
{
    WalkSpeed = Speed;
}

bool MoveManager::IsCurrentlyMoving() const
{
    return bIsMoving;
}

void MoveManager::UpdateAnimation(ENPCDirection Direction)
{
    if (!SpriteRenderer) return;

    std::string AnimationName;
    switch (Direction)
    {
    case ENPCDirection::UP:
        AnimationName = "Mother_Walk_Up";
        break;
    case ENPCDirection::DOWN:
        AnimationName = "Mother_Idle_Down";
        break;
    case ENPCDirection::LEFT:
        AnimationName = "Mother_Walk_Left";
        break;
    case ENPCDirection::RIGHT:
        AnimationName = "Mother_Walk_Right";
        break;
    default:
        return;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}

void MoveManager::SetDirection(ENPCDirection Direction)
{
   

    CurrentDirection = Direction;
    UpdateAnimation(Direction);
}