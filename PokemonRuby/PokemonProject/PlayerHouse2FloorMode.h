#pragma once
#include <EngineCore/GameMode.h>

class APlayerHouse2FloorMode : public AGameMode
{
public:
	static FIntPoint PlayerHouse2FloorMapModeChangePos;

	// 持失切 社瑚切
	APlayerHouse2FloorMode();
	~APlayerHouse2FloorMode();

	// delete funcion

	APlayerHouse2FloorMode(const APlayerHouse2FloorMode& _Other) = delete;
	APlayerHouse2FloorMode(APlayerHouse2FloorMode&& _Other) noexcept = delete;
	APlayerHouse2FloorMode& operator=(const APlayerHouse2FloorMode& _Other) = delete;
	APlayerHouse2FloorMode& operator=(APlayerHouse2FloorMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void LevelChange();

	void LevelChangeStart() override;

protected:

private:
	
};

