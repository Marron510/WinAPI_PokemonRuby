#include "PreCompile.h"
#include "SelectPokemonMap.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"
#include "SelectPokemonMode.h"

ASelectPokemonMap::ASelectPokemonMap()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("PokemonSelect.png");

	FVector2D Scale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(Scale.Half());
}

ASelectPokemonMap::~ASelectPokemonMap()
{

}