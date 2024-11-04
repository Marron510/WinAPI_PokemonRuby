#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "TitleMap.h"

ATitleGameMode::ATitleGameMode()
{

}

ATitleGameMode::~ATitleGameMode()
{

}


void ATitleGameMode::BeginPlay()
{
	ATitleMap* NewActor = GetWorld()->SpawnActor<ATitleMap>();

}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1");
	}

}