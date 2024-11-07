#pragma once
#include <EngineCore/Actor.h>

class APlayerHouse1Map : public AActor
{
public:
	// constrcuter destructer
	APlayerHouse1Map();
	~APlayerHouse1Map();

	// delete Function
	APlayerHouse1Map(const APlayerHouse1Map& _Other) = delete;
	APlayerHouse1Map(APlayerHouse1Map&& _Other) noexcept = delete;
	APlayerHouse1Map& operator=(const APlayerHouse1Map& _Other) = delete;
	APlayerHouse1Map& operator=(APlayerHouse1Map&& _Other) noexcept = delete;
	USpriteRenderer* GetCurMap()
	{
		return SpriteRenderer;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer;
};

