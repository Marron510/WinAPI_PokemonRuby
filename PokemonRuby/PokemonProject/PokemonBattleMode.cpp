#include "PreCompile.h"
#include "PokemonBattleMode.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>


#include "PokemonBattleMap.h"
#include "MyPokemon.h"
#include "WildPokemon.h"


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
		APokemonBattleMap* BackImage = GetWorld()->SpawnActor<APokemonBattleMap>();
		Map = BackImage->GetCurMap();
		
		
	}
	{
		AMyPokemon* Pokemon = GetWorld()->SpawnActor<AMyPokemon>();
		
	}

	{
		AWildPokemon* WildPokemon = GetWorld()->SpawnActor<AWildPokemon>();
		WildPokemon->SetActorLocation({ 500,500 });
	}
}
