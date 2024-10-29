#pragma once
#include <EngineCore/Actor.h>

class APokemonMap : public AActor
{
public:
	// constrcuter destructer
	APokemonMap();
	~APokemonMap();

	// delete Function
	APokemonMap(const APokemonMap& _Other) = delete;
	APokemonMap(APokemonMap&& _Other) noexcept = delete;
	APokemonMap& operator=(const APokemonMap& _Other) = delete;
	APokemonMap& operator=(APokemonMap&& _Other) noexcept = delete;

protected:

private:

};

