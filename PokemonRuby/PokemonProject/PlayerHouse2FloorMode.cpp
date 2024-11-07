#include "PreCompile.h"
#include "PlayerHouse2FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PlayerHouse2FloorMap.h"

APlayerHouse2FloorMode::APlayerHouse2FloorMode()
{

}

APlayerHouse2FloorMode::~APlayerHouse2FloorMode()
{

}


void APlayerHouse2FloorMode::BeginPlay()
{
	{
		APlayerHouse2FloorMap* NewActor = GetWorld()->SpawnActor<APlayerHouse2FloorMap>();
		Map = NewActor->GetCurMap();
	}
}

void APlayerHouse2FloorMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("LaborProfessorBirch");
	}

}