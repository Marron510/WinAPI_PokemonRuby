#include "PreCompile.h"
#include "TitleGameMode.h"



#include <EngineBase/TimeEvent.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>

#include "Fade.h"


ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	UEngineInput::GetInst().EnableInput();

	AFade* Actor = GetWorld()->SpawnActor<AFade>();
	Actor->FadeOut();

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Intro_0", 0);
	Sprite->SetSpriteScale(1.0f);
	Sprite->CreateAnimation("Intro0", "Intro_0", 0, 63, 0.1f, false);
	Sprite->CreateAnimation("Intro1", "Intro_1", 0, 166, 0.1f, false);
	Sprite->CreateAnimation("Intro2", "Intro_2", 0, 154, 0.1f, false);
	Sprite->CreateAnimation("Intro3", "Intro_3", 0, 223, 0.1f, true);
	Sprite->ChangeAnimation("Intro0");
	Sprite->SetComponentLocation({ 600, 400 });

	TimeEventer.PushEvent(9.0f, [this]()
		{
			PlayNextAnimation(); 
		});
	TimeEventer.PushEvent(25.6f, [this]()
		{
			PlayNextAnimation(); 
		});
	TimeEventer.PushEvent(42.0f, [this]()
		{
			PlayNextAnimation(); 
		});
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (!bIntro3Active && UEngineInput::GetInst().IsDown('Z'))
	{
		PlayNextAnimation();
	}
	if (UEngineInput::GetInst().IsDown('Z'))
	{
		StopCurrentSound();
		PlayNextSound();
	}

	if (!BGMPlayer.IsPlaying())
	{
		PlayNextSound();
	}

	if (bIntro3Active && UEngineInput::GetInst().IsDown('Z'))
	{
		BGMPlayer.Stop();
		UEngineAPICore::GetCore()->OpenLevel("Truck");
	}
}



void ATitleGameMode::PlayNextAnimation()
{
	if (bIntro3Active)
	{
		return;
	}

	switch (CurrentAnimationIndex)
	{
	case 0:
		Sprite->ChangeAnimation("Intro1");
		break;
	case 1:
		Sprite->ChangeAnimation("Intro2");
		break;
	case 2:
		Sprite->ChangeAnimation("Intro3");
		++CurrentAnimationIndex; 
		return;                  
	case 3:
		bIntro3Active = true;    
		return;
	}

	++CurrentAnimationIndex;

	ResetTimeEvent();
}



void ATitleGameMode::ResetTimeEvent()
{
	TimeEventer.ResetAllEvents();

	switch (CurrentAnimationIndex)
	{
	case 1:
		TimeEventer.PushEvent(16.6f, [this]() 
			{
				PlayNextAnimation();
			});
		break;
	case 2:
		TimeEventer.PushEvent(16.4f, [this]() 
			{
				PlayNextAnimation(); 
			}); 
		break;
	}
}


void ATitleGameMode::PlayNextSound()
{
	if (currentSoundIndex >= soundQueue.size())
	{
		return;
	}

	std::string soundName = soundQueue[currentSoundIndex];
	BGMPlayer = UEngineSound::Play(soundName);
	++currentSoundIndex;
}


void ATitleGameMode::StopCurrentSound()
{
	if (BGMPlayer.IsPlaying())
	{
		BGMPlayer.Stop();  
	}
}