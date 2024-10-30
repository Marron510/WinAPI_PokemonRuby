#pragma once
#include <EngineCore/GameMode.h>

class APokemonGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APokemonGameMode();
	~APokemonGameMode();

	// delete Function
	APokemonGameMode(const APokemonGameMode& _Other) = delete;
	APokemonGameMode(APokemonGameMode&& _Other) noexcept = delete;
	APokemonGameMode& operator=(const APokemonGameMode& _Other) = delete;
	APokemonGameMode& operator=(APokemonGameMode&& _Other) noexcept = delete;

	void BeginPlay();

protected:

private:

};

