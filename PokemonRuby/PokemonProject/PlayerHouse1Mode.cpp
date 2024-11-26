#include "PreCompile.h"
#include "PlayerHouse1Mode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PlayerHouse1Map.h"
#include "Player.h"

#include "PlayerHouse1FloorMode.h"
#include "Fade.h"

FIntPoint APlayerHouse1Mode::PlayerHouse1MapModeChangePos;

APlayerHouse1Mode::APlayerHouse1Mode()
{
}

APlayerHouse1Mode::~APlayerHouse1Mode()
{
}

void APlayerHouse1Mode::BeginPlay()
{
	Super::BeginPlay();
	{
		APlayerHouse1Map* NewActor = GetWorld()->SpawnActor<APlayerHouse1Map>();
		Map = NewActor->GetCurMap();
		APlayer* Player = GetWorld()->GetPawn<APlayer>();
		Player->SetColImage("PlayerHouse_1 Collision.png");
	}
	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
	}
}

void APlayerHouse1Mode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelChange();
}

void APlayerHouse1Mode::LevelChange()
{
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();


	FTileVector TargetPos1 = { 8, 1 };
	FTileVector TargetPos1NextLevelPos = { 8, 3 }; // house1floor 계단 입구


	if (MainPlayerLocation == TargetPos1.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1Floor");
		APlayerHouse1FloorMode::APlayerHouse1FloorModeChangePos = { 9 , 3 };
		Fade->FadeOut();
	}

}


void APlayerHouse1Mode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { PlayerHouse1MapModeChangePos.X, PlayerHouse1MapModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}

