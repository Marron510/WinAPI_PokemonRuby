#pragma once
#include <EngineCore/GameMode.h>

class APokemonMapMode : public AGameMode
{
public:
	// 持失切 社瑚切
	APokemonMapMode();
	~APokemonMapMode();

	// delete funcion

	APokemonMapMode(const APokemonMapMode& _Other) = delete;
	APokemonMapMode(APokemonMapMode&& _Other) noexcept = delete;
	APokemonMapMode& operator=(const APokemonMapMode& _Other) = delete;
	APokemonMapMode& operator=(APokemonMapMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

protected:

private:
	class ATileMap* GroundTileMap = nullptr;
};


