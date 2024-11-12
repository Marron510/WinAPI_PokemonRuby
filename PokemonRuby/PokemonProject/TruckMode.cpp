#include "PreCompile.h"
#include "TruckMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "TruckMap.h"
#include "Player.h"
#include "PokemonMapMode.h"

ATruckMode::ATruckMode()
{

}

ATruckMode::~ATruckMode()
{

}


void ATruckMode::BeginPlay()
{
	{
		FTileVector StartPos = { 2, 2 };
		ATruckMap* NewActor = GetWorld()->SpawnActor<ATruckMap>();
		Map = NewActor->GetCurMap();
		UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->SetActorLocation(StartPos.ToFVector());
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
		APokemonMapMode::PokemonMapModeChangePos = { 92 , 70 };
	}
	if (MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 92 , 70 };
	}
}
