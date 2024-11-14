#include "PreCompile.h"
#include "PokemonBattleMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"
#include "PokemonBattleMode.h"

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
		EnemyPokemonShadow = CreateDefaultSubObject<USpriteRenderer>();
		EnemyPokemonShadow->SetOrder(ERenderOrder::POKEMONSHADOW);
		EnemyPokemonShadow->SetSprite("EnemyPokemonShadow.png");
		FVector2D Scale = EnemyPokemonShadow->SetSpriteScale(1.0f);
		EnemyPokemonShadow->SetComponentLocation({ 840 , 308 }); // 적 포켓몬 타일의 최종 도착지점 추후 수정예정
	}

	{
		PlayerPokemonShadow = CreateDefaultSubObject<USpriteRenderer>();
		PlayerPokemonShadow->SetOrder(ERenderOrder::POKEMONSHADOW);
		PlayerPokemonShadow->SetSprite("PlayerPokemonShadow.png");
		FVector2D Scale = PlayerPokemonShadow->SetSpriteScale(1.0f);
		PlayerPokemonShadow->SetComponentLocation({ 336 , 520 }); // 내 포켓몬 타일의 최종 도착지점 추후 수정예정
	}

	{
		EnemyPokemonUI = CreateDefaultSubObject<USpriteRenderer>();
		EnemyPokemonUI->SetOrder(ERenderOrder::POKEMONSHADOW);
		EnemyPokemonUI->SetSprite("EnemyPokemonUI.png");
		FVector2D Scale = EnemyPokemonUI->SetSpriteScale(1.0f);
		EnemyPokemonUI->SetComponentLocation({ 336 , 166 }); // 적 상태 UI 위치 
	}

	{
		PlayerPokemonUI = CreateDefaultSubObject<USpriteRenderer>();
		PlayerPokemonUI->SetOrder(ERenderOrder::POKEMONSHADOW);
		PlayerPokemonUI->SetSprite("PlayerPokemonUI.png");
		FVector2D Scale = PlayerPokemonUI->SetSpriteScale(1.0f);
		PlayerPokemonUI->SetComponentLocation({ 902 , 460 }); // 타일의 최종 도착지점 추후 수정예정
	}



}

APokemonBattleMap::~APokemonBattleMap()
{

}