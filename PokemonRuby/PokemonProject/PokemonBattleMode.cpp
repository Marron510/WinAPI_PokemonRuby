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
		Pokemon->SetActorLocation({ 336 ,416 }); // 내 포켓몬 도착지점
	}

	{
		AWildPokemon* WildPokemon = GetWorld()->SpawnActor<AWildPokemon>();
		WildPokemon->SetActorLocation({ 1020,284 }); // 상대 포켓몬 도착지점
	}
}
