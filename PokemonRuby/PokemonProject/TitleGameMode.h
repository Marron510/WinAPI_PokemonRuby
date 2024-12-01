#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>

class ATitleGameMode : public AGameMode
{
public:
	// 持失切 社瑚切
	ATitleGameMode();
	~ATitleGameMode();

	// delete funcion

	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);
	void PlayNextAnimation();
	void ResetTimeEvent();
	void PlayNextSound();
	void StopCurrentSound();

protected:
private:
	class USpriteRenderer* Sprite = nullptr;
	int CurrentAnimationIndex = 0;
	bool bIntro3Active = false;

	std::vector<std::string> soundQueue = { "000_Title0.mp3","001_Title1.mp3", "002_Title2.mp3", "003_Title3.mp3" }; 
	size_t currentSoundIndex = 0;  
	class USoundPlayer BGMPlayer;
};

