#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>

#include "TitleMap.h"
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
		AtitleMap* NewActor = GetWorld()->SpawnActor<AtitleMap>();
	}
	
	{
		AFade* Actor = GetWorld()->SpawnActor<AFade>();
		Actor->FadeOut();
	}

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Intro_0", 0);
	Sprite->SetSpriteScale(1.0f);
	Sprite->CreateAnimation("Intro0", "Intro_0", 0, 86, 0.11f, false);
	Sprite->ChangeAnimation("Intro0");
	Sprite->SetComponentLocation({600,400});
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UEngineInput::GetInst().ExecuteIfKeyPressed(0.0f, []()
		{
			UEngineAPICore::GetCore()->OpenLevel("Truck");
		});
}