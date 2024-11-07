#pragma once
#include <EngineCore/Actor.h>

class APlayerHouse2FloorMap : public AActor
{
public:
	// constrcuter destructer
	APlayerHouse2FloorMap();
	~APlayerHouse2FloorMap();

	// delete Function
	APlayerHouse2FloorMap(const APlayerHouse2FloorMap& _Other) = delete;
	APlayerHouse2FloorMap(APlayerHouse2FloorMap&& _Other) noexcept = delete;
	APlayerHouse2FloorMap& operator=(const APlayerHouse2FloorMap& _Other) = delete;
	APlayerHouse2FloorMap& operator=(APlayerHouse2FloorMap&& _Other) noexcept = delete;
	
	USpriteRenderer* GetCurMap()
	{
		return SpriteRenderer;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer;
};
