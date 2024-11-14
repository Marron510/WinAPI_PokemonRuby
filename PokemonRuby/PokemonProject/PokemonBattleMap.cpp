#include "PreCompile.h"
#include "PokemonBattleMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"
#include "PokemonBattleMode.h"


USpriteRenderer* APokemonBattleMap::SpriteRenderer = nullptr;
USpriteRenderer* APokemonBattleMap::PlayerPokemonShadow = nullptr;
USpriteRenderer* APokemonBattleMap::EnemyPokemonShadow = nullptr;
USpriteRenderer* APokemonBattleMap::PlayerPokemonUI = nullptr;
USpriteRenderer* APokemonBattleMap::EnemyPokemonUI = nullptr;



APokemonBattleMap::APokemonBattleMap()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("BattleMap.png");

		FVector2D Scale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(Scale.Half());
	}

}

APokemonBattleMap::~APokemonBattleMap()
{

}