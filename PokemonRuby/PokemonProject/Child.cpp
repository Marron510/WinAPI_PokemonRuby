#include "PreCompile.h"
#include "Child.h"

#include <EngineBase/TimeEvent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineCoreDebug.h>

#include "PokemonEnum.h"
#include "PokemonMath.h"

AChild::AChild()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentLocation({ 48, 24 });
}

AChild::~AChild()
{

}

void AChild::BeginPlay()
{
    Super::BeginPlay();

    SpriteRenderer->SetSprite("Child.png");
    SpriteRenderer->SetComponentScale({ 120.0f, 130.0f });
    SpriteRenderer->SetOrder(ERenderOrder::NPC);

    SpriteRenderer->CreateAnimation("Child_Idle_Up", "Child.png", 0, 0, 0.1f);
    SpriteRenderer->CreateAnimation("Child_Idle_Down", "Child.png", 1, 1, 0.1f);
    SpriteRenderer->CreateAnimation("Child_Idle_Left", "Child.png", 2, 2, 0.1f);
    SpriteRenderer->CreateAnimation("Child_Idle_Right", "Child.png", 3, 3, 0.1f);
}

void AChild::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


void AChild::SetLookDirection(ENPCDirection Direction)
{
    CurrentDirection = Direction;

    std::string AnimationName;
    switch (Direction)
    {
    case ENPCDirection::UP:
        AnimationName = "Child_Idle_Up";
        break;
    case ENPCDirection::DOWN:
        AnimationName = "Child_Idle_Down";
        break;
    case ENPCDirection::LEFT:
        AnimationName = "Child_Idle_Left";
        break;
    case ENPCDirection::RIGHT:
        AnimationName = "Child_Idle_Right";
        break;
    case ENPCDirection::NONE:
    default:
        AnimationName = "Child_Idle_Down";
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}