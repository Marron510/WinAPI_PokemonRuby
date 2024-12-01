#include "PreCompile.h"
#include "Mother.h"

#include <EngineBase/TimeEvent.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineCoreDebug.h>

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
    SpriteRenderer->SetOrder(ERenderOrder::NPC);

    SpriteRenderer->CreateAnimation("Mother_Walk_Down_Left_Arm", "Mother.png", 0, 1, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Down_Right_Arm", "Mother.png", 2, 3, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Up_Left_Arm", "Mother.png", 4, 5, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Up_Right_Arm", "Mother.png", 6, 7, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Right_Left_Arm", "Mother.png", 8, 9, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Right_Right_Arm", "Mother.png", 10, 11, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Left_Left_Arm", "Mother.png", 12, 13, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Walk_Left_Right_Arm", "Mother.png", 14, 15, 0.1f);

    SpriteRenderer->CreateAnimation("Mother_Idle_Down", "Mother.png", 0, 0, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Idle_Up", "Mother.png", 4, 4, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Idle_Right", "Mother.png", 8, 8, 0.1f);
    SpriteRenderer->CreateAnimation("Mother_Idle_Left", "Mother.png", 12, 12, 0.1f);

    FVector2D ActorLocation = GetActorLocation();
    CurrentPosition = FVector2D(ActorLocation.X, ActorLocation.Y);

  
}

void AMother::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);


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







void AMother::SetAnimationByDirection(ENPCDirection Direction)
{
    std::string AnimationName;

    switch (Direction)
    {
    case ENPCDirection::UP_Left_Arm:
        AnimationName = "Mother_Walk_Up_Left_Arm";
        break;
    case ENPCDirection::UP_Right_Arm:
        AnimationName = "Mother_Walk_Up_Right_Arm";
        break;
    case ENPCDirection::DOWN_Left_Arm:
        AnimationName = "Mother_Walk_Down_Left_Arm";
        break;
    case ENPCDirection::DOWN_Right_Arm:
        AnimationName = "Mother_Walk_Down_Right_Arm";
        break;
    case ENPCDirection::LEFT_Left_Arm:
        AnimationName = "Mother_Walk_Left_Left_Arm";
        break;
    case ENPCDirection::LEFT_Right_Arm:
        AnimationName = "Mother_Walk_Left_Right_Arm";
        break;
    case ENPCDirection::RIGHT_Left_Arm:
        AnimationName = "Mother_Walk_Right_Left_Arm";
        break;
    case ENPCDirection::RIGHT_Right_Arm:
        AnimationName = "Mother_Walk_Right_Right_Arm";
        break;
    case ENPCDirection::NONE:
    default:
        AnimationName = "Mother_Idle_Down";
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}


void AMother::SetTargetLocation(const FVector2D& Offset)
{
    FVector2D NewTargetLocation = CurrentPosition + Offset;
    TargetLocation = NewTargetLocation;
    IsMoving = true;
    MoveTime = 0.0f;

    if (Offset.X > 0)
        LastDirection = bIsLeftArm ? ENPCDirection::RIGHT_Left_Arm : ENPCDirection::RIGHT_Right_Arm;
    else if (Offset.X < 0)
        LastDirection = bIsLeftArm ? ENPCDirection::LEFT_Left_Arm : ENPCDirection::LEFT_Right_Arm;
    else if (Offset.Y > 0)
        LastDirection = bIsLeftArm ? ENPCDirection::DOWN_Left_Arm : ENPCDirection::DOWN_Right_Arm;
    else if (Offset.Y < 0)
        LastDirection = bIsLeftArm ? ENPCDirection::UP_Left_Arm : ENPCDirection::UP_Right_Arm;
    else
        LastDirection = ENPCDirection::NONE;

    bIsLeftArm = !bIsLeftArm; 

    SetAnimationByDirection(LastDirection); 
}



void AMother::SetLookDirection(ENPCDirection Direction)
{
    std::string AnimationName;

    switch (Direction)
    {
    case ENPCDirection::UP_Left_Arm:
    case ENPCDirection::UP_Right_Arm:
        AnimationName = "Mother_Idle_Up";
        break;
    case ENPCDirection::DOWN_Left_Arm:
    case ENPCDirection::DOWN_Right_Arm:
        AnimationName = "Mother_Idle_Down";
        break;
    case ENPCDirection::LEFT_Left_Arm:
    case ENPCDirection::LEFT_Right_Arm:
        AnimationName = "Mother_Idle_Left";
        break;
    case ENPCDirection::RIGHT_Left_Arm:
    case ENPCDirection::RIGHT_Right_Arm:
        AnimationName = "Mother_Idle_Right";
        break;
    case ENPCDirection::NONE:
    default:
        AnimationName = "Mother_Idle_Down";
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}
