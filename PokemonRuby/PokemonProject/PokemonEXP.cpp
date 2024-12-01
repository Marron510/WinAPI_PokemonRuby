#include "PreCompile.h"
#include "PokemonEXP.h"

#include <EngineCore/SpriteRenderer.h>
#include "PokemonEnum.h"


APokemonEXP::APokemonEXP()
{
    PokemonEXPBar = CreateDefaultSubObject<USpriteRenderer>();
    PokemonEXPBar->SetSprite("Exp.png");
    PokemonEXPBar->SetOrder(ERenderOrder::CURSOR);
    PokemonEXPBar->SetPivotType(PivotType::Left);
    PokemonEXPBar->SetSpriteScale(1.0f);
}

APokemonEXP::~APokemonEXP()
{

}

void APokemonEXP::BeginPlay()
{
    Super::BeginPlay();
}

void APokemonEXP::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

}
