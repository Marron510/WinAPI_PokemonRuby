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

	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 6, 13 };
	FTileVector TargetPos2 = { 7, 13 };

	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
	}


}