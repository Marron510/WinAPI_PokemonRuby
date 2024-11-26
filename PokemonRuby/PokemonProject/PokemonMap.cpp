#include "PreCompile.h"
#include "PokemonMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"


APokemonMap::APokemonMap()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::Tile);
		SpriteRenderer->SetSprite("PokemonMap.png");
		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}

	{
		ChatRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ChatRenderer->SetOrder(ERenderOrder::CHAT);
		ChatRenderer->SetSprite("Chatting.png");
		ChatRenderer->SetSpriteScale(1.0f);
		ChatRenderer->SetComponentLocation({ChatRenderer->GetComponentScale().Half().X, 560.0f });
	}
}

APokemonMap::~APokemonMap()
{

}
