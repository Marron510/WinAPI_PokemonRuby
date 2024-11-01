#pragma once
#include <EngineCore/GameMode.h>


class ATitleGameMode : public AGameMode
{
public:
	// ������ �Ҹ���
	ATitleGameMode();
	~ATitleGameMode();

	// delete funcion

	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:

};

