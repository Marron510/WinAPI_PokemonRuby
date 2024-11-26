#pragma once
#include <EngineCore/GameMode.h>

class ATruckMode : public AGameMode
{
public:
	// 持失切 社瑚切
	ATruckMode();
	~ATruckMode();

	// delete funcion

	ATruckMode(const ATruckMode& _Other) = delete;
	ATruckMode(ATruckMode&& _Other) noexcept = delete;
	ATruckMode& operator=(const ATruckMode& _Other) = delete;
	ATruckMode& operator=(ATruckMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void LevelChange();

	void MoveMapHorizontally(float Duration, int RepeatCount);
protected:

private:
	class APlayer* Player = nullptr;
	class AFade* Fade = nullptr;
	UTimeEvent TimeEventManager;
};

