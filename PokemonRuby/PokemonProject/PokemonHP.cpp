#include "PreCompile.h"
#include "PokemonHP.h"

#include <EngineCore/SpriteRenderer.h>
#include "PokemonEnum.h"


APokemonHP::APokemonHP()
{
    PokemonHpBar = CreateDefaultSubObject<USpriteRenderer>();
    PokemonHpBar->SetSprite("EnemyHpBar.png");
    PokemonHpBar->SetOrder(ERenderOrder::CURSOR);
    PokemonHpBar->SetPivotType(PivotType::Left);
    PokemonHpBar->SetSpriteScale(1.0f);
}

APokemonHP::~APokemonHP()
{

}

void APokemonHP::BeginPlay()
{
    Super::BeginPlay();
}

void APokemonHP::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

}

void APokemonHP::HpHalf()
{
    PokemonHpBar->SetSprite("EnemyHpBarYellow.png");
}

void APokemonHP::HpLow()
{
    PokemonHpBar->SetSprite("EnemyHpBarRed.png");
}

