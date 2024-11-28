#include "PreCompile.h"
#include "PlayerHouse1FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>

#include "Player.h"
#include "PokemonMath.h"
#include "PlayerHouse1FloorMap.h"

#include "PokemonMapMode.h"
#include "PlayerHouse1Mode.h"
#include "Fade.h"
#include "Mother.h"
#include "PokemonText.h"
 
FIntPoint APlayerHouse1FloorMode::APlayerHouse1FloorModeChangePos;
APlayer::EPlayerDir APlayerHouse1FloorMode::APlayerHouse1FloorModePlayerDir;

APlayerHouse1FloorMode::APlayerHouse1FloorMode()
{

}

APlayerHouse1FloorMode::~APlayerHouse1FloorMode()
{

}


void APlayerHouse1FloorMode::BeginPlay()
{
	Super::BeginPlay();
	
		APlayerHouse1FloorMap* NewActor = GetWorld()->SpawnActor<APlayerHouse1FloorMap>();
		Map = NewActor->GetCurMap();
		Chat = NewActor->GetChatRender();
		Chat->SetActive(false);
		Player = GetWorld()->GetPawn<APlayer>();
		Player->SetColImage("PlayerHouse1Floor Collision.png");
		Player->SetDirection(APlayerHouse1FloorModePlayerDir);
	
	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
	}

	{
		Mother = GetWorld()->SpawnActor<AMother>();
		FVector2D MotherPosition = { 9 * TileSize.X, 7 * TileSize.Y };
		Mother->SetActorLocation(MotherPosition);
		Mother->GetRender()->SetActive(true);
	}
	{
		ChatText = GetWorld()->SpawnActor<APokemonText>();
		ChatText->SetTextSpriteName("TextBlack.png");
		ChatText->SetTextScale({ 25.0f, 38.0f });
		ChatText->SetOrder(ERenderOrder::FONT);
		FVector2D ChatLocation = { 100,620 };
		ChatText->SetActorLocation(ChatLocation);
	}

	Floor1Event();

	

}

void APlayerHouse1FloorMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelChange();

	ChatText->PrintTextUpdate(_DeltaTime);


	if (UEngineInput::GetInst().IsDown('Z'))
	{
		DisplayNextDialogue(); 
	}
}

void APlayerHouse1FloorMode::LevelChange()
{
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 9, 9 };
	FTileVector TargetPos1NextLevelPos = { 85, 69 }; // house1 출구
	FTileVector TargetPos2 = { 10, 9 };
	FTileVector TargetPos2NextLevelPos = { 94 , 69 }; // house1 출구
	FTileVector TargetPos3 = { 9, 2 };
	FTileVector TargetPos3NextLevelPos = { 1, 2 }; // house1 2층 출구


	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 85 , 69 };
		Fade->FadeOut();
	}
	if (MainPlayerLocation == TargetPos3.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1");
		APlayerHouse1Mode::PlayerHouse1MapModeChangePos = { 8 , 2 };
		Fade->FadeOut();
	}

}



void APlayerHouse1FloorMode::LevelChangeStart()
{
	AActor* Actor = GetWorld()->GetPawn();

	FTileVector StartPos = { APlayerHouse1FloorModeChangePos.X, APlayerHouse1FloorModeChangePos.Y };

	Actor->SetActorLocation(StartPos.ToFVector());

}

void APlayerHouse1FloorMode::Floor1Event()
{
	TimeEventer.PushEvent(0.01f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->GetRender()->ChangeAnimation("Mother_Idle_Up");
			}
		});

	TimeEventer.PushEvent(0.3f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->SetTargetLocation({ 0.0f, -1 * TileSize.Y });
				Player->MoveToTile({ 9,7 });
			}
		});
	
	TimeEventer.PushEvent(0.6f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->SetTargetLocation({ 0.0f, -1 * TileSize.Y });
				Player->MoveToTile({ 9,6 });
			}
		});
	
	TimeEventer.PushEvent(0.9f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->SetTargetLocation({ -1 * TileSize.X, 0.0f });
				Player->MoveToTile({ 9,5 });
			}
		});
	
	TimeEventer.PushEvent(1.2f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->SetTargetLocation({ -1 * TileSize.X, 0.0f });
				Player->MoveToTile({ 8,5 });
			}
		});
	
	TimeEventer.PushEvent(1.5f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->SetTargetLocation({ -1 * TileSize.X, 0.0f });
				Player->MoveToTile({ 7,5 });
			}
		});
	
	TimeEventer.PushEvent(1.8f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->SetTargetLocation({ -1 * TileSize.X, 0.0f });
				Player->MoveToTile({ 6,5 });
			}
		});
	
	TimeEventer.PushEvent(2.1f, [this]()
		{
			if (Mother->GetRender() != nullptr)
			{
				Mother->GetRender()->ChangeAnimation("Mother_Idle_Right");
			}
		});
	TimeEventer.PushEvent(2.4f, [this]() {
		RenderChatAbovePlayer();
		if (!Dialogues.empty())
		{
			ChatText->SetText(Dialogues[CurrentDialogueIndex], 0.1f);
			CurrentDialogueIndex++;
		}
		});
}

void APlayerHouse1FloorMode::DisplayNextDialogue()
{
	ChatText->ClearText();

	if (CurrentDialogueIndex < Dialogues.size())
	{
		ChatText->SetText(Dialogues[CurrentDialogueIndex], 0.1f);
		CurrentDialogueIndex++;
	}
	else
	{
		Chat->SetActive(false);
		ChatText->SetActive(false);
	}
}


void APlayerHouse1FloorMode::RenderChatAbovePlayer()
{
	if (Player == nullptr || Chat == nullptr || ChatText == nullptr)
	{
		return;
	}

	FVector2D PlayerLocation = Player->GetActorLocation();

	FVector2D ChatLocation = PlayerLocation + FVector2D(0.0f, 260.0f);

	Chat->SetComponentLocation(ChatLocation);
	Chat->SetOrder(ERenderOrder::CHAT);
	Chat->SetActive(true);
}
