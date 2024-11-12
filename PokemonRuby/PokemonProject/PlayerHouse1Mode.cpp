#include "PreCompile.h"
#include "PlayerHouse1Mode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PlayerHouse1Map.h"
#include "Player.h"

APlayerHouse1Mode::APlayerHouse1Mode()
{
}

APlayerHouse1Mode::~APlayerHouse1Mode()
{
}

void APlayerHouse1Mode::BeginPlay()
{
	{
		APlayerHouse1Map* NewActor = GetWorld()->SpawnActor<APlayerHouse1Map>();
		Map = NewActor->GetCurMap();
	}
}

void APlayerHouse1Mode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	
	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 7, 1 };

	if (MainPlayerLocation == TargetPos1.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1Floor");
	}

}