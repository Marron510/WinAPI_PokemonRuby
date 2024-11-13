#pragma once
#include <EngineCore/Actor.h>

class APokemonBattle : public AActor
{
public:
	// 持失切 社瑚切
	APokemonBattle();
	~APokemonBattle();

	// delete funcion

	APokemonBattle(const APokemonBattle& _Other) = delete;
	APokemonBattle(APokemonBattle&& _Other) noexcept = delete;
	APokemonBattle& operator=(const APokemonBattle& _Other) = delete;
	APokemonBattle& operator=(APokemonBattle&& _Other) noexcept = delete;
	
	USpriteRenderer* GetCurMap()
	{
		return SpriteRenderer;
	}

protected:

private:

	USpriteRenderer* SpriteRenderer;

};

