#pragma once
#include <EngineCore/GameMode.h>

#include "TileMap.h"

// Ό³Έν :
class ATileMapMode : public AGameMode
{
public:
	// constrcuter destructer
	ATileMapMode();
	~ATileMapMode();

	// delete Function
	ATileMapMode(const ATileMapMode& _Other) = delete;
	ATileMapMode(ATileMapMode&& _Other) noexcept = delete;
	ATileMapMode& operator=(const ATileMapMode& _Other) = delete;
	ATileMapMode& operator=(ATileMapMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:


};

