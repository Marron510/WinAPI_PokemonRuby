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
	{
	}
	
	{
		AFade* Actor = GetWorld()->SpawnActor<AFade>();
		Actor->FadeOut();
	}

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Intro_0", 0);
	Sprite->SetSpriteScale(1.0f);
	Sprite->CreateAnimation("Intro0", "Intro_0", 0, 86, 0.1f, false);
	Sprite->CreateAnimation("Intro1", "Intro_1", 0, 166, 0.1f, false);
	Sprite->CreateAnimation("Intro2", "Intro_2", 0, 154, 0.1f, false);
	Sprite->CreateAnimation("Intro3", "Intro_3", 0, 223, 0.1f, false);
	Sprite->ChangeAnimation("Intro0");
	Sprite->SetComponentLocation({600,400});


	TimeEventer.PushEvent(9.0f, [this]()
		{
			Sprite->ChangeAnimation("Intro1");
		});
	TimeEventer.PushEvent(25.6f, [this]()
		{
			Sprite->ChangeAnimation("Intro2");
		});
	TimeEventer.PushEvent(42.0f, [this]()
		{
			Sprite->ChangeAnimation("Intro3");
		});


}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UEngineInput::GetInst().ExecuteIfKeyPressed(0.0f, []()
		{
			UEngineAPICore::GetCore()->OpenLevel("Truck");
		});
}

