#include "PreCompile.h"
#include "PlayerHouse2FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PokemonMath.h"
#include "PlayerHouse2FloorMap.h"

#include "Player.h"
#include "PlayerHouse2Mode.h"
#include "PokemonMapMode.h"
#include "Fade.h"

FIntPoint APlayerHouse2FloorMode::PlayerHouse2FloorMapModeChangePos;
APlayer::EPlayerDir APlayerHouse2FloorMode::APlayerHouse2FloorModePlayerDir;

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
		APlayer* Player = GetWorld()->GetPawn<APlayer>();
		Player->SetColImage("PlayerHouse2Floor Collision.png");
	}
	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
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

	FTileVector TargetPos1 = { 3, 9 };
	FTileVector TargetPos1NextLevelPos = { 85, 69 }; // house2 입구
	FTileVector TargetPos2 = { 2, 9 };
	FTileVector TargetPos2NextLevelPos = { 94, 69 }; // house2 입구
	FTileVector TargetPos3 = { 3, 2 };
	FTileVector TargetPos3NextLevelPos = { 3, 2 }; // 2층 출구


	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 94 , 69 };
		Fade->FadeOut();
	}
	if (MainPlayerLocation == TargetPos3.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2");
		APlayerHouse2Mode::PlayerHouse2MapModeChangePos = { 2 , 2 };
		Fade->FadeOut();
	}
}


void APlayerHouse2FloorMode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { PlayerHouse2FloorMapModeChangePos.X, PlayerHouse2FloorMapModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}
