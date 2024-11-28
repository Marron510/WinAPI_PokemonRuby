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
USpriteRenderer* APokemonBattleMap::SelectMenu = nullptr;
USpriteRenderer* APokemonBattleMap::BattleSelectMenu = nullptr;
USpriteRenderer* APokemonBattleMap::BattleText = nullptr;

APokemonBattleMap::APokemonBattleMap()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("BattleMap.png");

		FVector2D Scale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(Scale.Half());
	}

	{
		BattleText = CreateDefaultSubObject<USpriteRenderer>();
		BattleText->SetOrder(ERenderOrder::WATER);
		BattleText->SetSprite("BattleMap1.png");

		FVector2D Scale = BattleText->SetSpriteScale(1.0f);
		BattleText->SetComponentLocation({ 600,680 });
	}

	{
		SelectMenu = CreateDefaultSubObject<USpriteRenderer>();
		SelectMenu->SetOrder(ERenderOrder::WATER);
		SelectMenu->SetSprite("BattleMap2.png");

		FVector2D Scale = SelectMenu->SetSpriteScale(1.0f);
		SelectMenu->SetComponentLocation({ 600,680 });
	}

	{
		BattleSelectMenu = CreateDefaultSubObject<USpriteRenderer>();
		BattleSelectMenu->SetOrder(ERenderOrder::WATER);
		BattleSelectMenu->SetSprite("BattleMap3.png");

		FVector2D Scale = BattleSelectMenu->SetSpriteScale(1.0f);
		BattleSelectMenu->SetComponentLocation({ 600,680 });
	}


	{
		PlayerPokemonShadow = CreateDefaultSubObject<USpriteRenderer>();
		PlayerPokemonShadow->SetOrder(ERenderOrder::POKEMONSHADOW);
		PlayerPokemonShadow->SetSprite("PlayerPokemonShadow.png");
		FVector2D Scale = PlayerPokemonShadow->SetSpriteScale(1.0f);
		PlayerPokemonShadow->SetComponentLocation({ 1500 , 520 }); 
	}

	{
		EnemyPokemonShadow = CreateDefaultSubObject<USpriteRenderer>();
		EnemyPokemonShadow->SetOrder(ERenderOrder::POKEMONSHADOW);
		EnemyPokemonShadow->SetSprite("EnemyPokemonShadow.png");
		FVector2D Scale = EnemyPokemonShadow->SetSpriteScale(1.0f);
		EnemyPokemonShadow->SetComponentLocation({ -360 , 308 }); 
	}

	{
		PlayerPokemonUI = CreateDefaultSubObject<USpriteRenderer>();
		PlayerPokemonUI->SetOrder(ERenderOrder::SKILLEFFECT);
		PlayerPokemonUI->SetSprite("PlayerPokemonUI.png");
		FVector2D Scale = PlayerPokemonUI->SetSpriteScale(1.0f);
		PlayerPokemonUI->SetComponentLocation({ 1600 , 460 }); 
	}

	{
		EnemyPokemonUI = CreateDefaultSubObject<USpriteRenderer>();
		EnemyPokemonUI->SetOrder(ERenderOrder::POKEMONSHADOW);
		EnemyPokemonUI->SetSprite("EnemyPokemonUI.png");
		FVector2D Scale = EnemyPokemonUI->SetSpriteScale(1.0f);
		EnemyPokemonUI->SetComponentLocation({ -400 , 166 }); 
	}
}

APokemonBattleMap::~APokemonBattleMap()
{

}