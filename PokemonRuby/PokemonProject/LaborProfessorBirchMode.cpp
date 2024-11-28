#include "PreCompile.h"
#include "LaborProfessorBirchMode.h"

#include <EngineBase/TimeEvent.h>

#include<EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>


#include "Player.h"
#include "Professor.h"
#include "LaborProfessorBirchMap.h"
#include "PokemonMapMode.h"
#include "Fade.h"

FIntPoint ALaborProfessorBirchMode::LaborProfessorBirchModeChangePos;
APlayer::EPlayerDir ALaborProfessorBirchMode::ALaborProfessorBirchModePlayerDir;

ALaborProfessorBirchMode::ALaborProfessorBirchMode()
{

}

ALaborProfessorBirchMode::~ALaborProfessorBirchMode()
{

}


void ALaborProfessorBirchMode::BeginPlay()
{
	Super::BeginPlay();
	{
		ALaborProfessorBirchMap* NewActor = GetWorld()->SpawnActor<ALaborProfessorBirchMap>();
		Map = NewActor->GetCurMap();
		Player = GetWorld()->GetPawn<APlayer>();
		Player->SetColImage("LaborProfessorBirch Collision.png");
	}
	{
		Professor = GetWorld()->SpawnActor<AProfessor>();
		FVector2D ProfessorPosition = { 7 * TileSize.X, 4 * TileSize.Y };
		Professor->SetActorLocation(ProfessorPosition);
		Professor->GetRender()->SetActive(true);
	}

	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
	}
	UEngineInput::GetInst().EnableInput();

	TimeEventer.PushEvent(0.05f, [this]()
		{
			Player->GetPlayerRender()->ChangeAnimation("Idle_Left_Right_Arm");
			Professor->GetRender()->ChangeAnimation("Professor_Idle_Right");
		});


}

void ALaborProfessorBirchMode::Tick(float _DeltaTime)
{


	Super::Tick(_DeltaTime);

	LevelChange(_DeltaTime);
	
}

void ALaborProfessorBirchMode::LevelChange(float _DeltaTime)
{
	AActor* MainPlayer = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn();
	FVector2D MainPlayerLocation = MainPlayer->GetActorLocation();


	FTileVector TargetPos1 = { 6, 13 };
	FTileVector TargetPos1NextLevelPos = { 87, 77 }; // 楷备家 免备
	FTileVector TargetPos2 = { 7, 13 };
	FTileVector TargetPos2NextLevelPos = { 87, 77 }; // 楷备家 免备

	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		MainPlayer->SetActorLocation(TargetPos1.ToFVector() + FTileVector::Up.ToFVector());
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 87, 77 };
		Fade->FadeOut();
	}
}



void ALaborProfessorBirchMode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();
	
	FTileVector StartPos = { LaborProfessorBirchModeChangePos.X, LaborProfessorBirchModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}

