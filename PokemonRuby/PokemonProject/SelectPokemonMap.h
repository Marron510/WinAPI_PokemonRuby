#pragma once
#include <EngineCore/Actor.h>

class ASelectPokemonMap : public AActor
{
public:
	// 持失切 社瑚切
	ASelectPokemonMap();
	~ASelectPokemonMap();

	// delete funcion

	ASelectPokemonMap(const ASelectPokemonMap& _Other) = delete;
	ASelectPokemonMap(ASelectPokemonMap&& _Other) noexcept = delete;
	ASelectPokemonMap& operator=(const ASelectPokemonMap& _Other) = delete;
	ASelectPokemonMap& operator=(ASelectPokemonMap&& _Other) noexcept = delete;

	USpriteRenderer* GetCurMap()
	{
		return SpriteRenderer;
	}

protected:

private:
	class USpriteRenderer* SpriteRenderer;
	
};

