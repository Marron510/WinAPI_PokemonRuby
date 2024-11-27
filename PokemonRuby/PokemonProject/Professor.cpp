#include "PreCompile.h"
#include "Professor.h"

#include <EngineBase/TimeEvent.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineCoreDebug.h>

#include "PokemonEnum.h"
#include "PokemonMath.h"


AProfessor::AProfessor()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentLocation({ 48, 24 });
}

AProfessor::~AProfessor()
{

}

void AProfessor::BeginPlay()
{
    Super::BeginPlay();

    SpriteRenderer->SetSprite("Professor.png");
    SpriteRenderer->SetComponentScale({ 120.0f, 130.0f });
    SpriteRenderer->SetOrder(ERenderOrder::NPC);

    SpriteRenderer->CreateAnimation("Professor_Walk_Down_Left_Arm", "Professor.png", 4, 5, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Walk_Down_Right_Arm", "Professor.png", 4, 5, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Walk_Up_Left_Arm", "Professor.png", 6, 7, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Walk_Up_Right_Arm", "Professor.png", 6, 7, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Walk_Right_Left_Arm", "Professor.png", 2, 3, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Walk_Right_Right_Arm", "Professor.png", 2, 3, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Walk_Left_Left_Arm", "Professor.png", 0, 1, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Walk_Left_Right_Arm", "Professor.png", 0, 1, 0.1f);

    SpriteRenderer->CreateAnimation("Professor_Idle_Down", "Professor.png", 4, 4, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Idle_Up", "Professor.png", 6, 6, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Idle_Right", "Professor.png", 2, 2, 0.1f);
    SpriteRenderer->CreateAnimation("Professor_Idle_Left", "Professor.png", 0, 0, 0.1f);

    FVector2D ActorLocation = GetActorLocation();
    CurrentPosition = FVector2D(ActorLocation.X, ActorLocation.Y);


}

void AProfessor::Tick(float _DeltaTime)
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







void AProfessor::SetAnimationByDirection(ENPCDirection Direction)
{
    std::string AnimationName;

    switch (Direction)
    {
    case ENPCDirection::UP_Left_Arm:
        AnimationName = "Professor_Walk_Up_Left_Arm";
        break;
    case ENPCDirection::UP_Right_Arm:
        AnimationName = "Professor_Walk_Up_Right_Arm";
        break;
    case ENPCDirection::DOWN_Left_Arm:
        AnimationName = "Professor_Walk_Down_Left_Arm";
        break;
    case ENPCDirection::DOWN_Right_Arm:
        AnimationName = "Professor_Walk_Down_Right_Arm";
        break;
    case ENPCDirection::LEFT_Left_Arm:
        AnimationName = "Professor_Walk_Left_Left_Arm";
        break;
    case ENPCDirection::LEFT_Right_Arm:
        AnimationName = "Professor_Walk_Left_Right_Arm";
        break;
    case ENPCDirection::RIGHT_Left_Arm:
        AnimationName = "Professor_Walk_Right_Left_Arm";
        break;
    case ENPCDirection::RIGHT_Right_Arm:
        AnimationName = "Professor_Walk_Right_Right_Arm";
        break;
    case ENPCDirection::NONE:
    default:
        AnimationName = "Professor_Idle_Down";
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}


void AProfessor::SetTargetLocation(const FVector2D& Offset)
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



void AProfessor::SetLookDirection(ENPCDirection Direction)
{
    std::string AnimationName;

    switch (Direction)
    {
    case ENPCDirection::UP_Left_Arm:
    case ENPCDirection::UP_Right_Arm:
        AnimationName = "Professor_Idle_Up";
        break;
    case ENPCDirection::DOWN_Left_Arm:
    case ENPCDirection::DOWN_Right_Arm:
        AnimationName = "Professor_Idle_Down";
        break;
    case ENPCDirection::LEFT_Left_Arm:
    case ENPCDirection::LEFT_Right_Arm:
        AnimationName = "Professor_Idle_Left";
        break;
    case ENPCDirection::RIGHT_Left_Arm:
    case ENPCDirection::RIGHT_Right_Arm:
        AnimationName = "Professor_Idle_Right";
        break;
    case ENPCDirection::NONE:
    default:
        AnimationName = "Professor_Idle_Down";
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}
