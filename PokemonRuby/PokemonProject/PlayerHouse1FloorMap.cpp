#include "PreCompile.h"
#include "PlayerHouse1FloorMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"


APlayerHouse1FloorMap::APlayerHouse1FloorMap()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("PlayerHouse1Floor.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}

	{
		ChatRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ChatRenderer->SetOrder(ERenderOrder::CHAT);
		ChatRenderer->SetSprite("Chatting.png");
		ChatRenderer->SetSpriteScale(1.0f);
		ChatRenderer->SetComponentLocation({ ChatRenderer->GetComponentScale().Half().X, 560.0f });
	}
}

APlayerHouse1FloorMap::~APlayerHouse1FloorMap()
{

}
