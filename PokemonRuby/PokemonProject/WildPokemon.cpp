#include "PreCompile.h"
#include "WildPokemon.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineRandom.h>


#include "PokemonEnum.h"
#include "TargetPokemon.h"
#include "PokemonStat.h"


AWildPokemon::AWildPokemon()
{
    UEngineRandom Random;

    EWildPokemonEnum selectedPokemonEnum = static_cast<EWildPokemonEnum>(Random.RandomInt(0, 2));

    switch (selectedPokemonEnum)
    {
    case EWildPokemonEnum::Zigzagoon:
        PokemonName = "ZIGZAGOON";
        break;
    case EWildPokemonEnum::Poochyena:
        PokemonName = "POOCHYENA";
        break;
    case EWildPokemonEnum::Wurmple:
        PokemonName = "WURMPLE";
        break;
    default:
        PokemonName = "Unknown";
        break;
    }

    WildPokemonRender = CreateDefaultSubObject<USpriteRenderer>();
    WildPokemonRender->SetSprite(PokemonName + ".png");
    WildPokemonRender->CreateAnimation(PokemonName, PokemonName + ".png", 0, 0, 0.2f);
    WildPokemonRender->ChangeAnimation(PokemonName);
    WildPokemonRender->SetOrder(ERenderOrder::POKEMON);
    WildPokemonRender->SetSpriteScale(1.0f);

}
	

AWildPokemon::~AWildPokemon()
{

}




void AWildPokemon::BeginPlay()
{
	Super::BeginPlay();
}

void AWildPokemon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

int AWildPokemon::AdjustLevelByRegion(int baseLevel, int regionLevel)
{
    UEngineRandom Random;
    int RegionRandom = Random.RandomInt(1, 3);
    int adjustedLevel = baseLevel + RegionRandom + regionLevel;
    return adjustedLevel;  // 레벨을 조정하여 반환
}


void AWildPokemon::EncounterWildPokemon(int regionLevel)
{
    UEngineRandom Random;

    int randomPokemonEnum = Random.RandomInt(static_cast<int>(EWildPokemonEnum::Zigzagoon), static_cast<int>(EWildPokemonEnum::Wurmple));
    EWildPokemonEnum selectedPokemonEnum = static_cast<EWildPokemonEnum>(randomPokemonEnum);

    int baseLevel = 1;

    int adjustedLevel = AdjustLevelByRegion(baseLevel, regionLevel);

    PokemonStats<ZigzagoonStats> stats(adjustedLevel);

    ATargetPokemon encounteredPokemon;
    encounteredPokemon.SetName(selectedPokemonEnum == EWildPokemonEnum::Zigzagoon ? "Zigzagoon" : "Wurmple");
    encounteredPokemon.SetLevel(adjustedLevel);
    encounteredPokemon.SetHP(stats.GetHP());
    encounteredPokemon.SetAttack(stats.GetAttack());
    encounteredPokemon.SetDefense(stats.GetDefense());
    encounteredPokemon.SetSpecialAttack(stats.GetSpecialAttack());
    encounteredPokemon.SetSpecialDefense(stats.GetSpecialDefense());
    encounteredPokemon.SetSpeed(stats.GetSpeed());

    EncounteredPokemon = &encounteredPokemon;
    
}
