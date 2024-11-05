#include "PreCompile.h"
#include "LaborProfessorBirchMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

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
	}
}

void ALaborProfessorBirchMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
	}

}