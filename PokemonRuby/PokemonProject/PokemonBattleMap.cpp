#include "PreCompile.h"
#include "PokemonBattleMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

APokemonBattleMap::APokemonBattleMap()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("BattleMap.png");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());
}

APokemonBattleMap::~APokemonBattleMap()
{

}