#include "PreCompile.h"
#include "PokemonBattleMode.h"
#include "PokemonBattleMap.h"

APokemonBattleMode::APokemonBattleMode()
{

}

APokemonBattleMode::~APokemonBattleMode()
{

}

void APokemonBattleMode::BeginPlay()
{
	Super::BeginPlay();

	{
		APokemonBattleMap* NewActor = GetWorld()->SpawnActor<APokemonBattleMap>();
		Map = NewActor->GetCurMap();
	}
}


void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}