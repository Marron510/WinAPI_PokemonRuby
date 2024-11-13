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

protected:

private:

	USpriteRenderer* SpriteRenderer;

};

