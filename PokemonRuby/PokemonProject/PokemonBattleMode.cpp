#include "PreCompile.h"
#include "PokemonBattleMode.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>


#include "PokemonMath.h"
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
		PlayerPokemonShadow = BackImage->GetPlayerPKMShadow ();
		EnemyPokemonShadow = BackImage->GetEnemyPokemonShadow();
		PlayerPokemonUI = BackImage->GetPokemonUI();
		EnemyPokemonUI = BackImage->GetEnemyPokemonUI();
	}

	{
		AMyPokemon* Pokemon = GetWorld()->SpawnActor<AMyPokemon>();
		Pokemon->SetActorLocation({ 336 ,416 }); // 내 포켓몬 도착지점
	}

	{
		AWildPokemon* WildPokemon = GetWorld()->SpawnActor<AWildPokemon>();
		WildPokemon->SetActorLocation({ 1020,260 }); // 상대 포켓몬 도착지점
	}

	
}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	//FVector2D TargetLocation = FVector2D({ 1200 , 460 });
	//FVector2D NewLocation = UPokemonMath::Lerp(, TargetLocation, _DeltaTime);
	//SetActorLocation(NewLocation);

}
// PlayerPokemonUI->SetComponentLocation({ 902 , 460 });