#pragma once
#include <EngineCore/GameMode.h>

class APokemonMapMode : public AGameMode
{
public:
	static FIntPoint PokemonMapModeChangePos;

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

	void LevelChange();

	void LevelChangeStart() override;

	
protected:

private:
	class AFade* Fade = nullptr;
	
};


