#include "PreCompile.h"
#include "Monster.h"

#include <EngineBase/TimeEvent.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineCoreDebug.h>

#include "PokemonEnum.h"
#include "PokemonMath.h"
AMonster::AMonster()
{
    SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
    SpriteRenderer->SetComponentLocation({ 48, 24 });
}

AMonster::~AMonster()
{

}


void AMonster::BeginPlay()
{
    Super::BeginPlay();

    SpriteRenderer->SetSprite("Monster.png");
    SpriteRenderer->SetComponentScale({ 120.0f, 130.0f });
    SpriteRenderer->SetOrder(ERenderOrder::NPC);

    SpriteRenderer->CreateAnimation("Monster_Walk_Down", "Monster.png", 0, 1, 0.1f);
    SpriteRenderer->CreateAnimation("Monster_Walk_Up", "Monster.png", 2, 3, 0.1f);
    SpriteRenderer->CreateAnimation("Monster_Walk_Left", "Monster.png", 0, 1, 0.1f);
    SpriteRenderer->CreateAnimation("Monster_Walk_Right", "Monster.png", 2, 3, 0.1f);
    

    SpriteRenderer->CreateAnimation("Monster_Idle_Down", "Monster.png", 0, 0, 0.1f);
    SpriteRenderer->CreateAnimation("Monster_Idle_Up", "Monster.png", 2, 2, 0.1f);
    SpriteRenderer->CreateAnimation("Monster_Idle_Left", "Monster.png", 0, 0, 0.1f);
    SpriteRenderer->CreateAnimation("Monster_Idle_Right", "Monster.png", 2, 2, 0.1f);

    FVector2D ActorLocation = GetActorLocation();
    CurrentPosition = FVector2D(ActorLocation.X, ActorLocation.Y);


}

void AMonster::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    TimeEventer.Update(_DeltaTime);

    if (IsMoving)
    {
        MoveTime += _DeltaTime * MoveSpeed;

        FVector2D NewPosition = UPokemonMath::Lerp(CurrentPosition, TargetLocation, MoveTime);

        SetActorLocation(FVector2D(NewPosition.X, NewPosition.Y));

        if ((TargetLocation - NewPosition).Length() < 1.0f)
        {
            CurrentPosition = TargetLocation;
            SetActorLocation(FVector2D(TargetLocation.X, TargetLocation.Y));
            IsMoving = false;

            SetLookDirection(LastDirection);
        }
    }
}

void AMonster::SetTargetLocation(const FVector2D& Offset)
{
    FVector2D NewTargetLocation = CurrentPosition + Offset;
    TargetLocation = NewTargetLocation;
    IsMoving = true;
    MoveTime = 0.0f;

    if (Offset.X > 0)
        LastDirection = ENPCDirection::RIGHT;
    else if (Offset.X < 0)
        LastDirection = ENPCDirection::LEFT;
    else if (Offset.Y > 0)
        LastDirection = ENPCDirection::DOWN;
    else if (Offset.Y < 0)
        LastDirection = ENPCDirection::UP;
    else
        LastDirection = ENPCDirection::NONE;

    SetAnimationByDirection(LastDirection);
}

void AMonster::SetAnimationByDirection(ENPCDirection Direction)
{
    std::string AnimationName;

    switch (Direction)
    {
    case ENPCDirection::UP:
        AnimationName = "Monster_Walk_Up";
        break;
    case ENPCDirection::DOWN:
        AnimationName = "Monster_Walk_Down";
        break;
    case ENPCDirection::LEFT:
        AnimationName = "Monster_Walk_Left";
        break;
    case ENPCDirection::RIGHT:
        AnimationName = "Monster_Walk_Right";
        break;
    case ENPCDirection::NONE:
    default:
        AnimationName = "Monster_Idle_Down";
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}

void AMonster::SetLookDirection(ENPCDirection Direction)
{
    std::string AnimationName;

    switch (Direction)
    {
    case ENPCDirection::UP:
        AnimationName = "Monster_Idle_Up";
        break;
    case ENPCDirection::DOWN:
        AnimationName = "Monster_Idle_Down";
        break;
    case ENPCDirection::LEFT:
        AnimationName = "Monster_Idle_Left";
        break;
    case ENPCDirection::RIGHT:
        AnimationName = "Monster_Idle_Right";
        break;
    case ENPCDirection::NONE:
    default:
        AnimationName = "Monster_Idle_Down";
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}