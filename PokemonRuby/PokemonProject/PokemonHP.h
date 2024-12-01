#pragma once
#include <EngineCore/Actor.h>

class APokemonHP : public AActor
{
public:
	// 持失切 社瑚切
	APokemonHP();
	~APokemonHP();

	// delete funcion

	APokemonHP(const APokemonHP& _Other) = delete;
	APokemonHP(APokemonHP&& _Other) noexcept = delete;
	APokemonHP& operator=(const APokemonHP& _Other) = delete;
	APokemonHP& operator=(APokemonHP&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* GetRender()
	{
		return PokemonHpBar;
	}

	void HpHalf();
	void HpLow();

protected:

private:
	class USpriteRenderer* PokemonHpBar;
};

