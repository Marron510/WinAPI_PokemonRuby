#include "PreCompile.h"
#include "PokemonBattleMode.h"
#include "PokemonBattle.h"

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
		APokemonBattle* NewActor = GetWorld()->SpawnActor<APokemonBattle>();
		Map = NewActor->GetCurMap();
	}
}


void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}