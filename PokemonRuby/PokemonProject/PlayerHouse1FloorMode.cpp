#include "PreCompile.h"
#include "PlayerHouse1FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PokemonMath.h"
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
		Map = NewActor->GetCurMap();
	}
}

void APlayerHouse1FloorMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelChange();
}

void APlayerHouse1FloorMode::LevelChange()
{
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 8, 9 };
	FTileVector TargetPos1NextLevelPos = { 85, 69 }; // house1 출구
	FTileVector TargetPos2 = { 9, 9 };
	FTileVector TargetPos2NextLevelPos = { 85, 69 }; // house1 출구
	FTileVector TargetPos3 = { 8, 2 };
	FTileVector TargetPos3NextLevelPos = { 1, 2 }; // house1 2층 출구


	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
	}
	if (MainPlayerLocation == TargetPos3.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1");
	}
}
