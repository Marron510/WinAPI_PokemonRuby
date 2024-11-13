#include "PreCompile.h"
#include "PlayerHouse1FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "Player.h"
#include "PokemonMath.h"
#include "PlayerHouse1FloorMap.h"

#include "PokemonMapMode.h"
#include "PlayerHouse1Mode.h"
 
FIntPoint APlayerHouse1FloorMode::APlayerHouse1FloorModeChangePos;

APlayerHouse1FloorMode::APlayerHouse1FloorMode()
{

}

APlayerHouse1FloorMode::~APlayerHouse1FloorMode()
{

}


void APlayerHouse1FloorMode::BeginPlay()
{
	Super::BeginPlay();
	{
		APlayerHouse1FloorMap* NewActor = GetWorld()->SpawnActor<APlayerHouse1FloorMap>();
		Map = NewActor->GetCurMap();
		APlayer* Player = GetWorld()->GetPawn<APlayer>();
		Player->SetColImage("PlayerHouse1Floor Collision.png");
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
	FTileVector TargetPos2NextLevelPos = { 94 , 69 }; // house1 출구
	FTileVector TargetPos3 = { 9, 2 };
	FTileVector TargetPos3NextLevelPos = { 1, 2 }; // house1 2층 출구


	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 85 , 69 };
	}
	if (MainPlayerLocation == TargetPos3.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1");
		APlayerHouse1Mode::PlayerHouse1MapModeChangePos = { 8 , 2 };
	}
}



void APlayerHouse1FloorMode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { APlayerHouse1FloorModeChangePos.X, APlayerHouse1FloorModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}

