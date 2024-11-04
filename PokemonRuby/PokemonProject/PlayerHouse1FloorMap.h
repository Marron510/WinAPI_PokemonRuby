#pragma once
#include <EngineCore/Actor.h>

class APlayerHouse1FloorMap : public AActor
{
public:
	// constrcuter destructer
	APlayerHouse1FloorMap();
	~APlayerHouse1FloorMap();

	// delete Function
	APlayerHouse1FloorMap(const APlayerHouse1FloorMap& _Other) = delete;
	APlayerHouse1FloorMap(APlayerHouse1FloorMap&& _Other) noexcept = delete;
	APlayerHouse1FloorMap& operator=(const APlayerHouse1FloorMap& _Other) = delete;
	APlayerHouse1FloorMap& operator=(APlayerHouse1FloorMap&& _Other) noexcept = delete;

protected:

private:

};

