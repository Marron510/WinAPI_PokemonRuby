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
		Chat = NewActor->GetChatRender();
		Chat->SetActive(false);
		Player = GetWorld()->GetPawn<APlayer>();
		Player->SetColImage("LaborProfessorBirch Collision.png");
		Player->SetDirection(ALaborProfessorBirchModePlayerDir);
		Player->DisableMovement();
	}
	{
		Professor = GetWorld()->SpawnActor<AProfessor>();
		FVector2D ProfessorPosition = { 7 * TileSize.X, 4 * TileSize.Y };
		Professor->SetActorLocation(ProfessorPosition);
		Professor->GetRender()->SetActive(true);
	}

	
	{
		ChatText = GetWorld()->SpawnActor<APokemonText>();
		ChatText->SetTextSpriteName("TextBlack.png");
		ChatText->SetTextScale({ 24.0f, 38.0f });
		ChatText->SetOrder(ERenderOrder::FONT);
		FVector2D ChatLocation = { 100,620 };
		ChatText->SetActorLocation(ChatLocation);
	}

	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
	}

	UEngineInput::GetInst().EnableInput();

	TimeEventer.PushEvent(0.05f, [this]()
		{
			Professor->GetRender()->ChangeAnimation("Professor_Idle_Right");
			RenderChatAbovePlayer();
		});
	TimeEventer.PushEvent(0.1f, [this]()
		{
			StartProfessorDialogue();
		});
	
}

void ALaborProfessorBirchMode::Tick(float _DeltaTime)
{


	Super::Tick(_DeltaTime);

	LevelChange(_DeltaTime);
	
	if (ChatText->IsActive() && UEngineInput::GetInst().IsDown('Z'))
	{
		DisplayNextDialogue(); 
	}
	
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
		UEngineSound::AllSoundStop();
		BGMPlayer = UEngineSound::Play("005_MishiroTown.mp3");
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

void ALaborProfessorBirchMode::StartProfessorDialogue()
{
	ChatText->SetActive(true);
	ChatText->SetText(Dialogues[CurrentDialogueIndex], 0.1f); 
	CurrentDialogueIndex++;
}

void ALaborProfessorBirchMode::DisplayNextDialogue()
{
	ChatText->ClearText();

	if (CurrentDialogueIndex < Dialogues.size())
	{
		BGMPlayer = UEngineSound::Play("SEClick.mp3");
		ChatText->SetText(Dialogues[CurrentDialogueIndex], 0.03f);
		CurrentDialogueIndex++;
	}
	else
	{
		BGMPlayer = UEngineSound::Play("SEClick.mp3");
		ChatText->SetActive(false);
		Chat->SetActive(false);
		Player->EnableMovement();
	}
}


void ALaborProfessorBirchMode::RenderChatAbovePlayer()
{
	if (Player == nullptr || Chat == nullptr || ChatText == nullptr)
	{
		return;
	}

	FVector2D PlayerLocation = Player->GetActorLocation();

	FVector2D ChatLocation = PlayerLocation + FVector2D(0.0f, 270.0f);

	Chat->SetComponentLocation(ChatLocation);
	Chat->SetOrder(ERenderOrder::CHAT);
	Chat->SetActive(true);
}
