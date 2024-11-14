#include "PreCompile.h"
#include "PokemonBattleMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

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
		USpriteRenderer* EnemyPokemonShadow = CreateDefaultSubObject<USpriteRenderer>();
		EnemyPokemonShadow->SetOrder(ERenderOrder::POKEMONSHADOW);
		EnemyPokemonShadow->SetSprite("EnemyPokemonShadow.png");
		FVector2D Scale = EnemyPokemonShadow->SetSpriteScale(1.0f);
		EnemyPokemonShadow->SetComponentLocation({ 840 , 332 }); // 타일의 최종 도착지점 추후 수정예정
	}

	{
		USpriteRenderer* PlayerPokemonShadow = CreateDefaultSubObject<USpriteRenderer>();
		PlayerPokemonShadow->SetOrder(ERenderOrder::POKEMONSHADOW);
		PlayerPokemonShadow->SetSprite("PlayerPokemonShadow.png");
		FVector2D Scale = PlayerPokemonShadow->SetSpriteScale(1.0f);
		PlayerPokemonShadow->SetComponentLocation({ 336 , 520 }); // 타일의 최종 도착지점 추후 수정예정
	}

	{
		USpriteRenderer* EnemyPokemonUI = CreateDefaultSubObject<USpriteRenderer>();
		EnemyPokemonUI->SetOrder(ERenderOrder::POKEMONSHADOW);
		EnemyPokemonUI->SetSprite("EnemyPokemonUI.png");
		FVector2D Scale = EnemyPokemonUI->SetSpriteScale(1.0f);
		EnemyPokemonUI->SetComponentLocation({ 336 , 520 }); // 타일의 최종 도착지점 추후 수정예정
	}

	{
		USpriteRenderer* PlayerPokemonUI = CreateDefaultSubObject<USpriteRenderer>();
		PlayerPokemonUI->SetOrder(ERenderOrder::POKEMONSHADOW);
		PlayerPokemonUI->SetSprite("PlayerPokemonUI.png");
		FVector2D Scale = PlayerPokemonUI->SetSpriteScale(1.0f);
		PlayerPokemonUI->SetComponentLocation({ 840 , 520 }); // 타일의 최종 도착지점 추후 수정예정
	}



}

APokemonBattleMap::~APokemonBattleMap()
{

}