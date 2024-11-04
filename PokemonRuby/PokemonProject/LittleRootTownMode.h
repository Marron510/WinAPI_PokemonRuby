#pragma once
#include <EngineCore/GameMode.h>

class ALittleRootTownMode : public AGameMode
{
public:
	// 持失切 社瑚切
	ALittleRootTownMode();
	~ALittleRootTownMode();

	// delete funcion

	ALittleRootTownMode(const ALittleRootTownMode& _Other) = delete;
	ALittleRootTownMode(ALittleRootTownMode&& _Other) noexcept = delete;
	ALittleRootTownMode& operator=(const ALittleRootTownMode& _Other) = delete;
	ALittleRootTownMode& operator=(ALittleRootTownMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

protected:

private:

};

