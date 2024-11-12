#include "PreCompile.h"
#include "PlayerHouse2FloorMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PokemonMath.h"
#include "PlayerHouse2FloorMap.h"

APlayerHouse2FloorMode::APlayerHouse2FloorMode()
{

}

APlayerHouse2FloorMode::~APlayerHouse2FloorMode()
{

}


void APlayerHouse2FloorMode::BeginPlay()
{
	{
		APlayerHouse2FloorMap* NewActor = GetWorld()->SpawnActor<APlayerHouse2FloorMap>();
		Map = NewActor->GetCurMap();
	}
}

void APlayerHouse2FloorMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D MainPlayerLocation = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	FTileVector TargetPos1 = { 1, 9 };
	FTileVector TargetPos2 = { 2, 9 };
	FTileVector TargetPos3 = { 2, 2 };

	if (MainPlayerLocation == TargetPos1.ToFVector() || MainPlayerLocation == TargetPos2.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PokemonMap");
	}
	if (MainPlayerLocation == TargetPos3.ToFVector())
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2");
	}

}