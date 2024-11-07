#include "PreCompile.h"
#include "PlayerHouse1FloorMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"


APlayerHouse1FloorMap::APlayerHouse1FloorMap()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("PlayerHouse1Floor.png");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());

}

APlayerHouse1FloorMap::~APlayerHouse1FloorMap()
{

}
