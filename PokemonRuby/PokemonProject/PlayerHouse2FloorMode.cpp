#include "PreCompile.h"
#include "PlayerHouse2FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PokemonMath.h"
#include "PlayerHouse2FloorMap.h"

#include "PlayerHouse2Mode.h"
#include "PokemonMapMode.h"


FIntPoint APlayerHouse2FloorMode::PlayerHouse2FloorMapModeChangePos;

APlayerHouse2FloorMode::APlayerHouse2FloorMode()
{

}

APlayerHouse2FloorMode::~APlayerHouse2FloorMode()
{

}


void APlayerHouse2FloorMode::BeginPlay()
{
	Super::BeginPlay();
	{
		APlayerHouse2FloorMap* NewActor = GetWorld()->SpawnActor<APlayerHouse2FloorMap>();
		Map = NewActor->GetCurMap();
	}
}

void APlayerHouse2FloorMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelChange();
}

void APlayerHouse2FloorMode::LevelChange()
{
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 1, 9 };
	FTileVector TargetPos1NextLevelPos = { 85, 69 }; // house1 입구
	FTileVector TargetPos2 = { 2, 9 };
	FTileVector TargetPos2NextLevelPos = { 94, 69 }; // house2 입구
	FTileVector TargetPos3 = { 2, 2 };
	FTileVector TargetPos3NextLevelPos = { 1, 2 }; // 2층 출구


	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 94 , 69 };
	}
	if (MainPlayerLocation == TargetPos3.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2");
		APlayerHouse2Mode::PlayerHouse2MapModeChangePos = { 1 , 2 };
	}
}


void APlayerHouse2FloorMode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { PlayerHouse2FloorMapModeChangePos.X, PlayerHouse2FloorMapModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}
