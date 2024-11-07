#include "PreCompile.h"
#include "PlayerHouse2FloorMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"


APlayerHouse2FloorMap::APlayerHouse2FloorMap()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("PlayerHouse2Floor.png");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());

}

APlayerHouse2FloorMap::~APlayerHouse2FloorMap()
{

}
