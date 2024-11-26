#include "PreCompile.h"
#include "TruckMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "TruckMap.h"
#include "Player.h"
#include "PokemonMapMode.h"
#include "Fade.h"


ATruckMode::ATruckMode()
{

}

ATruckMode::~ATruckMode()
{

}


void ATruckMode::BeginPlay()
{
	
	Player = GetWorld()->GetPawn<APlayer>();
	FTileVector StartPos = { 2, 2 };
	ATruckMap* NewActor = GetWorld()->SpawnActor<ATruckMap>();
	Map = NewActor->GetCurMap();
	UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->SetActorLocation(StartPos.ToFVector());
	
	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
	}
}

void ATruckMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	LevelChange();
}

void ATruckMode::LevelChange()
{
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 5, 2 };
	FTileVector TargetPos2 = { 5, 3 };


	if (MainPlayerLocation == TargetPos1.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 84 , 70 };
		APokemonMapMode::PokemonMapModePlayerDir = APlayer::EPlayerDir::RIGHT_Left_Arm;
		Fade->FadeOut();
		Player->SetDirection(APlayer::EPlayerDir::RIGHT_Left_Arm);
	}
	if (MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 84 , 70 };
		APokemonMapMode::PokemonMapModePlayerDir = APlayer::EPlayerDir::RIGHT_Left_Arm;
		Fade->FadeOut();
	}
}
