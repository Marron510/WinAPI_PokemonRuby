#pragma once
#include <EngineCore/Actor.h>

class APokemonBattleMap : public AActor
{
public:

	// 持失切 社瑚切
	APokemonBattleMap();
	~APokemonBattleMap();

	// delete funcion

	APokemonBattleMap(const APokemonBattleMap& _Other) = delete;
	APokemonBattleMap(APokemonBattleMap&& _Other) noexcept = delete;
	APokemonBattleMap& operator=(const APokemonBattleMap& _Other) = delete;
	APokemonBattleMap& operator=(APokemonBattleMap&& _Other) noexcept = delete;
	
	USpriteRenderer* GetCurMap()
	{
		return SpriteRenderer;
	}

	USpriteRenderer* GetPlayerPKMShadow()
	{
		return PlayerPokemonShadow;
	}

	USpriteRenderer* GetEnemyPokemonShadow()
	{
		return EnemyPokemonShadow;
	}

	USpriteRenderer* GetPokemonUI()
	{
		return PlayerPokemonUI;
	}

	USpriteRenderer* GetEnemyPokemonUI()
	{
		return EnemyPokemonUI;
	}

	USpriteRenderer* GetSelectMenu()
	{
		return SelectMenu;
	}

	USpriteRenderer* GetBattleSelectMenu()
	{
		return BattleSelectMenu;
	}
	USpriteRenderer* GetBattleText()
	{
		return BattleText;
	}

protected:

private:

	static USpriteRenderer* SpriteRenderer;
	static USpriteRenderer* PlayerPokemonShadow;
	static USpriteRenderer* EnemyPokemonShadow;
	static USpriteRenderer* PlayerPokemonUI;
	static USpriteRenderer* EnemyPokemonUI;
	static USpriteRenderer* SelectMenu;
	static USpriteRenderer* BattleSelectMenu;
	static USpriteRenderer* BattleText;
};

