#pragma once
#include <EngineCore/Actor.h>

class APlayerHouse2Map : public AActor
{
public:
	// constrcuter destructer
	APlayerHouse2Map();
	~APlayerHouse2Map();

	// delete Function
	APlayerHouse2Map(const APlayerHouse2Map& _Other) = delete;
	APlayerHouse2Map(APlayerHouse2Map&& _Other) noexcept = delete;
	APlayerHouse2Map& operator=(const APlayerHouse2Map& _Other) = delete;
	APlayerHouse2Map& operator=(APlayerHouse2Map&& _Other) noexcept = delete;

protected:

private:

};

