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

}

AMonster::~AMonster()
{

}


void AMonster::BeginPlay()
{
    Super::BeginPlay();

    SpriteRenderer->SetSprite("Moster.png");
    SpriteRenderer->SetComponentScale({ 120.0f, 130.0f });
    SpriteRenderer->SetOrder(ERenderOrder::NPC);

    SpriteRenderer->CreateAnimation("Moster_Walk_Down", "Moster.png", 0, 1, 0.1f);
    SpriteRenderer->CreateAnimation("Moster_Walk_Up", "Moster.png", 2, 3, 0.1f);
    SpriteRenderer->CreateAnimation("Moster_Walk_Left", "Moster.png", 0, 1, 0.1f);
    SpriteRenderer->CreateAnimation("Moster_Walk_Right", "Moster.png", 2, 3, 0.1f);
    

    SpriteRenderer->CreateAnimation("Moster_Idle_Down", "Moster.png", 0, 0, 0.1f);
    SpriteRenderer->CreateAnimation("Moster_Idle_Up", "Moster.png", 2, 2, 0.1f);
    SpriteRenderer->CreateAnimation("Moster_Idle_Left", "Moster.png", 0, 0, 0.1f);
    SpriteRenderer->CreateAnimation("Moster_Idle_Right", "Moster.png", 2, 2, 0.1f);

    FVector2D ActorLocation = GetActorLocation();
    CurrentPosition = FVector2D(ActorLocation.X, ActorLocation.Y);


}
