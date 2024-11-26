#include "PreCompile.h"
#include "Mother.h"

#include <EngineBase/TimeEvent.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineCoreDebug.h>

#include "MoveManager.h"
#include "PokemonEnum.h"
#include "PokemonMath.h"

AMother::AMother()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
   	SpriteRenderer->SetComponentLocation({ 48, 24 });
}


AMother::~AMother()
{
	
}



void AMother::BeginPlay()
{
    Super::BeginPlay();

    SpriteRenderer->SetSprite("Mother.png");
    SpriteRenderer->SetComponentScale({ 120.0f, 130.0f });
    SpriteRenderer->SetOrder(ERenderOrder::PLAYER);

    SpriteRenderer->CreateAnimation("Mother_Walk_Down", "Mother.png", 0, 3, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Up", "Mother.png", 4, 7, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Right", "Mother.png", 8, 11, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Left", "Mother.png", 12, 15, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Idle_Down", "Mother.png", 0, 0, 0.1f);

    FVector2D ActorLocation = GetActorLocation();
    CurrentPosition = FVector2D(ActorLocation.X, ActorLocation.Y);

    TimeEventer.PushEvent(2.0f, [this]() {
        SetTargetLocation({ 0.0f, 96.0f });
        });
    TimeEventer.PushEvent(3.0f, [this]() {
        SetTargetLocation({ 0.0f, 96.0f });
        });
}

void AMother::Tick(float _DeltaTime)
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
            CurrentDirection = ENPCDirection::NONE;
            SetAnimationByDirection(ENPCDirection::NONE);
        }
    }
}





void AMother::SetAnimationByDirection(ENPCDirection Direction)
{
    switch (Direction)
    {
    case ENPCDirection::UP:
        SpriteRenderer->ChangeAnimation("Mother_Walk_Up");
        break;
    case ENPCDirection::DOWN:
        SpriteRenderer->ChangeAnimation("Mother_Walk_Down");
        break;
    case ENPCDirection::LEFT:
        SpriteRenderer->ChangeAnimation("Mother_Walk_Left");
        break;
    case ENPCDirection::RIGHT:
        SpriteRenderer->ChangeAnimation("Mother_Walk_Right");
        break;
    case ENPCDirection::NONE:
    default:
        SpriteRenderer->ChangeAnimation("Mother_Idle_Down");
        break;
    }
}

void AMother::SetTargetLocation(const FVector2D& Offset)
{
    FVector2D NewTargetLocation = CurrentPosition + Offset;
    TargetLocation = NewTargetLocation;
    IsMoving = true;
    MoveTime = 0.0f;

    if (Offset.X > 0)
        CurrentDirection = ENPCDirection::RIGHT;
    else if (Offset.X < 0)
        CurrentDirection = ENPCDirection::LEFT;
    else if (Offset.Y > 0)
        CurrentDirection = ENPCDirection::DOWN;
    else if (Offset.Y < 0)
        CurrentDirection = ENPCDirection::UP;
    else
        CurrentDirection = ENPCDirection::NONE;

    SetAnimationByDirection(CurrentDirection);
}

