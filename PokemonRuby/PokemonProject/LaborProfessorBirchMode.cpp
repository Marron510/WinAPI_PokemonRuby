#include "PreCompile.h"
#include "LaborProfessorBirchMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PokemonMath.h"
#include "LaborProfessorBirchMap.h"

ALaborProfessorBirchMode::ALaborProfessorBirchMode()
{

}

ALaborProfessorBirchMode::~ALaborProfessorBirchMode()
{

}


void ALaborProfessorBirchMode::BeginPlay()
{
	{
		ALaborProfessorBirchMap* NewActor = GetWorld()->SpawnActor<ALaborProfessorBirchMap>();
		Map = NewActor->GetCurMap();
	}
}

void ALaborProfessorBirchMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelChange();
}

void ALaborProfessorBirchMode::LevelChange()
{
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 6, 13 };
	FTileVector TargetPos1NextLevelPos = { 87, 77 }; // 楷备家 免备
	FTileVector TargetPos2 = { 7, 13 };
	FTileVector TargetPos2NextLevelPos = { 87, 77 }; // 楷备家 免备

	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
	}
}
