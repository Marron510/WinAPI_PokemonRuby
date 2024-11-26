#include "PreCompile.h"
#include "PlayerHouse2Mode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PlayerHouse2Map.h"
#include "Player.h"

#include "PlayerHouse2FloorMode.h"
#include "Fade.h"

FIntPoint APlayerHouse2Mode::PlayerHouse2MapModeChangePos;
APlayer::EPlayerDir APlayerHouse2Mode::PlayerHouse2MapModePlayerDir = APlayer::EPlayerDir::DOWN_Left_Arm;

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
		APlayer* Player = GetWorld()->GetPawn<APlayer>();
		Player->SetColImage("PlayerHouse_2Collision.png");
		Player->SetDirection(PlayerHouse2MapModePlayerDir);
	}
	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
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

	FTileVector TargetPos1 = { 2, 1 };
	FTileVector TargetPos1NextLevelPos = { 3, 3 }; // house2floor 계단 입구

	if (MainPlayerLocation == TargetPos1.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2Floor");
		APlayerHouse2FloorMode::PlayerHouse2FloorMapModeChangePos = { 3 , 3 };
		Fade->FadeOut();
	}
}



void APlayerHouse2Mode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { PlayerHouse2MapModeChangePos.X, PlayerHouse2MapModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}