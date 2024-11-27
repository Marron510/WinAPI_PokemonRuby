#pragma once
#include <EngineCore/Actor.h>

class SelectPokemonMap : public AActor
{
public:
	// 持失切 社瑚切
	SelectPokemonMap();
	~SelectPokemonMap();

	// delete funcion

	SelectPokemonMap(const SelectPokemonMap& _Other) = delete;
	SelectPokemonMap(SelectPokemonMap&& _Other) noexcept = delete;
	SelectPokemonMap& operator=(const SelectPokemonMap& _Other) = delete;
	SelectPokemonMap& operator=(SelectPokemonMap&& _Other) noexcept = delete;


protected:

private:
	static USpriteRenderer* SpriteRenderer;
};

