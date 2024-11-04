#pragma once
#include <EngineCore/GameMode.h>

class APlayerHouse2Mode : public AGameMode
{
public:
	// constrcuter destructer
	APlayerHouse2Mode();
	~APlayerHouse2Mode();

	// delete Function
	APlayerHouse2Mode(const APlayerHouse2Mode& _Other) = delete;
	APlayerHouse2Mode(APlayerHouse2Mode&& _Other) noexcept = delete;
	APlayerHouse2Mode& operator=(const APlayerHouse2Mode& _Other) = delete;
	APlayerHouse2Mode& operator=(APlayerHouse2Mode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

protected:

private:

};

