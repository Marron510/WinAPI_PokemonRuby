#include "PreCompile.h"
#include "PlayerHouse2Mode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PlayerHouse2Map.h"
#include "Player.h"


FIntPoint APlayerHouse2Mode::PlayerHouse2MapModeChangePos;

APlayerHouse2Mode::APlayerHouse2Mode()
{
}

APlayerHouse2Mode::~APlayerHouse2Mode()
{
}

void APlayerHouse2Mode::BeginPlay()
{
	Super::BeginPlay();
	{
		APlayerHouse2Map* NewActor = GetWorld()->SpawnActor<APlayerHouse2Map>();
		Map = NewActor->GetCurMap();
	}
}

void APlayerHouse2Mode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelChange();
}


void APlayerHouse2Mode::LevelChange()
{
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 1, 1 };
	FTileVector TargetPos1NextLevelPos = { 2, 3 }; // house2floor 계단 입구

	if (MainPlayerLocation == TargetPos1.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2Floor");
	}
}



void APlayerHouse2Mode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { PlayerHouse2MapModeChangePos.X, PlayerHouse2MapModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}