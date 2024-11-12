#pragma once
#include <EngineCore/GameMode.h>

class APlayerHouse1Mode : public AGameMode
{
public:
	// constrcuter destructer
	APlayerHouse1Mode();
	~APlayerHouse1Mode();

	// delete Function
	APlayerHouse1Mode(const APlayerHouse1Mode& _Other) = delete;
	APlayerHouse1Mode(APlayerHouse1Mode&& _Other) noexcept = delete;
	APlayerHouse1Mode& operator=(const APlayerHouse1Mode& _Other) = delete;
	APlayerHouse1Mode& operator=(APlayerHouse1Mode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void LevelChange();

protected:

private:

};

