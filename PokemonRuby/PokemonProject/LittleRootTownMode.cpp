#include "PreCompile.h"
#include "LittleRootTownMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "LittleRootTownMap.h"

ALittleRootTownMode::ALittleRootTownMode()
{

}

ALittleRootTownMode::~ALittleRootTownMode()
{

}


void ALittleRootTownMode::BeginPlay()
{
	{
		ALittleRootTownMap* NewActor = GetWorld()->SpawnActor<ALittleRootTownMap>();
	}
}

void ALittleRootTownMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2");
	}

}