#include "PreCompile.h"
#include "TruckMode.h"

#include <EngineBase/TimeEvent.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>

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
	Player->SetColImage("TruckCollision.png");
	FTileVector StartPos = { 2, 2 };
	ATruckMap* NewActor = GetWorld()->SpawnActor<ATruckMap>();
	Map = NewActor->GetCurMap();
	
	UEngineAPICore::GetCore()->GetCurLevel()->GetPawn()->SetActorLocation(StartPos.ToFVector());
	
	{
		Fade = GetWorld()->SpawnActor<AFade>();
		Fade->FadeOut();
	}
	Player->DisableMovement();

	TimeEventer.PushEvent(0.5f, [this]() {
		MoveMapHorizontally(10.0f, 30); 
		});
	TimeEventer.PushEvent(11.0f, [this]() {
		UEngineInput::GetInst().EnableInput();
		Player->EnableMovement();
		});
	TimeEventer.PushEvent(12.0f, [this]() {
		BGMPlayer = UEngineSound::Play("SEOpenTruck.mp3");
		Map->SetSprite("Truck.png");
		});

	BGMPlayer = UEngineSound::Play("004_Truck.mp3");
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
		BGMPlayer = UEngineSound::Play("SEMoveMap.mp3");
		TimeEventer.PushEvent(1.2f, [this]() {
			BGMPlayer.Stop();
			}); 
		Fade->FadeOut();

		Player->SetDirection(APlayer::EPlayerDir::RIGHT_Left_Arm);
	}
	if (MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
		APokemonMapMode::PokemonMapModeChangePos = { 84 , 70 };
		APokemonMapMode::PokemonMapModePlayerDir = APlayer::EPlayerDir::RIGHT_Left_Arm;
		BGMPlayer = UEngineSound::Play("SEMoveMap.mp3");
		TimeEventer.PushEvent(1.2f, [this]() {
			BGMPlayer.Stop();
			});
		Fade->FadeOut();
	}
}
void ATruckMode::MoveMapHorizontally(float Duration, int RepeatCount)
{
	if (!Map) return; 

	float Interval = Duration / (RepeatCount * 2);
	FVector2D OriginalLocation = Map->GetComponentLocation();
	FVector2D Offset = FVector2D(5.0f, 0.0f); 

	for (int i = 0; i < RepeatCount; ++i)
	{
		TimeEventer.PushEvent(i * 2 * Interval, [this, OriginalLocation, Offset]() {
			if (Map)
			{
				Map->SetComponentLocation(OriginalLocation + Offset);
			}
			});

		
		TimeEventer.PushEvent((i * 2 + 1) * Interval, [this, OriginalLocation, Offset]() {
			if (Map)
			{
				Map->SetComponentLocation(OriginalLocation - Offset);
			}
			});
	}

	TimeEventer.PushEvent(RepeatCount * 2 * Interval, [this, OriginalLocation]() {
		if (Map)
		{
			Map->SetComponentLocation(OriginalLocation);
		}
		});
}
