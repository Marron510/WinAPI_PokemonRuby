#include "PreCompile.h"
#include "PokemonBattleMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

APokemonBattleMap::APokemonBattleMap()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("BattleMap.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}

	{
		SpriteRendererShadow1 = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererShadow1->SetOrder(ERenderOrder::POKEMONSHADOW);
		SpriteRendererShadow1->SetSprite("PokemonTile.png");
		FVector2D MapScale = SpriteRendererShadow1->SetSpriteScale(1.0f);
		SpriteRendererShadow1->SetComponentLocation({ 840 , 332 }); // 타일의 최종 도착지점 추후 수정예정
	}

	{
		SpriteRendererShadow2 = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererShadow2->SetOrder(ERenderOrder::POKEMONSHADOW);
		SpriteRendererShadow2->SetSprite("PlayerTile.png");
		FVector2D MapScale = SpriteRendererShadow2->SetSpriteScale(1.0f);
		SpriteRendererShadow2->SetComponentLocation({ 336 , 520 }); // 타일의 최종 도착지점 추후 수정예정
	}
}

APokemonBattleMap::~APokemonBattleMap()
{

}