#include "PreCompile.h"
#include "PlayerHouse2Mode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PlayerHouse2Map.h"
#include "Player.h"

APlayerHouse2Mode::APlayerHouse2Mode()
{
}

APlayerHouse2Mode::~APlayerHouse2Mode()
{
}

void APlayerHouse2Mode::BeginPlay()
{
	{
		APlayerHouse2Map* NewActor = GetWorld()->SpawnActor<APlayerHouse2Map>();
		Map = NewActor->GetCurMap();
	}
}

void APlayerHouse2Mode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);



	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 1, 1 };

	if (MainPlayerLocation == TargetPos1.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2Floor");
	}

}