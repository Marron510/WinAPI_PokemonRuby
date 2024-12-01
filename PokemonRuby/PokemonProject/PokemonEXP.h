#pragma once
#include <EngineCore/Actor.h>

class APokemonEXP : public AActor
{
public:
	// 持失切 社瑚切
	APokemonEXP();
	~APokemonEXP();

	// delete funcion

	APokemonEXP(const APokemonEXP& _Other) = delete;
	APokemonEXP(APokemonEXP&& _Other) noexcept = delete;
	APokemonEXP& operator=(const APokemonEXP& _Other) = delete;
	APokemonEXP& operator=(APokemonEXP&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* GetRender()
	{
		return PokemonEXPBar;
	}

protected:

private:
	class USpriteRenderer* PokemonEXPBar;
};

