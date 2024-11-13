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
		APokemonBattleMap* BackImage = GetWorld()->SpawnActor<APokemonBattleMap>();
		Map = BackImage->GetCurMap();
		/*APokemonBattleMap* PokemonShadowImage = GetWorld()->SpawnActor<APokemonBattleMap>();
		APokemonBattleMap* PlayerShadowImage = GetWorld()->SpawnActor<APokemonBattleMap>();
		PokemonShadowImage->*/

	}
}


void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);






}