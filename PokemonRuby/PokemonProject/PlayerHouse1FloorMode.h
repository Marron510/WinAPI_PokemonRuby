#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"

class APlayerHouse1FloorMode : public AGameMode
{
public:
	static FIntPoint APlayerHouse1FloorModeChangePos;
	static APlayer::EPlayerDir APlayerHouse1FloorModePlayerDir;

	// 持失切 社瑚切
	APlayerHouse1FloorMode();
	~APlayerHouse1FloorMode();

	// delete funcion

	APlayerHouse1FloorMode(const APlayerHouse1FloorMode& _Other) = delete;
	APlayerHouse1FloorMode(APlayerHouse1FloorMode&& _Other) noexcept = delete;
	APlayerHouse1FloorMode& operator=(const APlayerHouse1FloorMode& _Other) = delete;
	APlayerHouse1FloorMode& operator=(APlayerHouse1FloorMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void LevelChange();

	void LevelChangeStart() override;

protected:

private:
	class APlayer* Player = nullptr;
	class AFade* Fade = nullptr;
};

