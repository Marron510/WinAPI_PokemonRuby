#include "PreCompile.h"
#include "PlayerHouse1FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PlayerHouse1FloorMap.h"

APlayerHouse1FloorMode::APlayerHouse1FloorMode()
{

}

APlayerHouse1FloorMode::~APlayerHouse1FloorMode()
{

}


void APlayerHouse1FloorMode::BeginPlay()
{
	{
		APlayerHouse1FloorMap* NewActor = GetWorld()->SpawnActor<APlayerHouse1FloorMap>();
	}
}

void APlayerHouse1FloorMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
	}

}