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
  
    int randomPokemonEnum = Random.RandomInt(static_cast<int>(EWildPokemonEnum::Zigzagoon), static_cast<int>(EWildPokemonEnum::Wurmple));  // 예시로 Zigzagoon을 선택
   
    EWildPokemonEnum selectedPokemonEnum = static_cast<EWildPokemonEnum>(randomPokemonEnum);

    std::vector<ATargetPokemon>& selectedPokemonVector = WildPokemons[selectedPokemonEnum];

    if (selectedPokemonVector.size() > 0)
    {
        ATargetPokemon& selectedPokemon = selectedPokemonVector[0];

        WildPokemonRender = CreateDefaultSubObject<USpriteRenderer>();
        WildPokemonRender->SetOrder(ERenderOrder::POKEMON);

        std::string spriteName = selectedPokemon.GetName(); // 포켓몬 이름을 기반으로 스프라이트 설정 (예: "Zigzagoon.png")
        WildPokemonRender->SetSprite(spriteName + ".png");

        FVector2D Scale = WildPokemonRender->SetSpriteScale(1.0f);  // 스프라이트 크기 설정
        WildPokemonRender->CreateAnimation(spriteName, spriteName + ".png", 0, 0, 0.2f);

        EncounteredPokemon = &selectedPokemon;
        // 추가적으로, 포켓몬의 레벨, 이름 등의 속성 설정이 가능함
        //int level = selectedPokemon.GetLevel();  // 레벨을 가져옴
        // 레벨에 따른 다른 속성도 설정 가능
    }
	
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
    // 1. 랜덤으로 포켓몬 선택 (예: Zigzagoon)
    UEngineRandom Random;
    int randomPokemonEnum = Random.RandomInt(static_cast<int>(EWildPokemonEnum::Zigzagoon), static_cast<int>(EWildPokemonEnum::Wurmple));
    EWildPokemonEnum selectedPokemonEnum = static_cast<EWildPokemonEnum>(randomPokemonEnum);

    // 2. 해당 포켓몬의 기본 레벨과 정보를 가져옴
    std::vector<ATargetPokemon>& selectedPokemonVector = WildPokemons[selectedPokemonEnum];
    ATargetPokemon& selectedPokemon = selectedPokemonVector[0];  // 첫 번째 포켓몬 선택

    int baseLevel = selectedPokemon.GetLevel();

    // 3. 지역에 맞게 포켓몬의 레벨을 조정
    int adjustedLevel = AdjustLevelByRegion(baseLevel, regionLevel);

    // 4. PokemonStats 클래스를 사용하여 능력치 계산
    PokemonStats<ZigzagoonStats> stats(adjustedLevel);  // 예시: ZigzagoonStats 클래스를 사용

    // 5. TargetPokemon 객체를 생성하고 능력치 적용
    ATargetPokemon encounteredPokemon;
    encounteredPokemon.SetName(selectedPokemon.GetName());
    encounteredPokemon.SetLevel(adjustedLevel);
    encounteredPokemon.SetHP(stats.GetHP());
    encounteredPokemon.SetAttack(stats.GetAttack());
    encounteredPokemon.SetDefense(stats.GetDefense());
    encounteredPokemon.SetSpecialAttack(stats.GetSpecialAttack());
    encounteredPokemon.SetSpecialDefense(stats.GetSpecialDefense());
    encounteredPokemon.SetSpeed(stats.GetSpeed());

    // 6. EncounteredPokemon을 이후 전투에서 사용
    EncounteredPokemon = &encounteredPokemon;
}
