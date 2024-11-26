#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>


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
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UEngineInput::GetInst().ExecuteIfKeyPressed(0.0f, []()
		{
			UEngineAPICore::GetCore()->OpenLevel("Truck");
		});
}