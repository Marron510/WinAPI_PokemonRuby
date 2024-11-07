#pragma once
#include "Actor.h"

class AGameMode : public AActor
{
public:
	// constrcuter destructer
	AGameMode();
	~AGameMode();

	// delete Function
	AGameMode(const AGameMode& _Other) = delete;
	AGameMode(AGameMode&& _Other) noexcept = delete;
	AGameMode& operator=(const AGameMode& _Other) = delete;
	AGameMode& operator=(AGameMode&& _Other) noexcept = delete;

	USpriteRenderer* GetMap()
	{
		return Map;
	}

protected:
	class ATileMap* GroundTileMap = nullptr;
	class USpriteRenderer* Map = nullptr;
	
private:

};

