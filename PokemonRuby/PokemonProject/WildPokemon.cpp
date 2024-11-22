#include "PreCompile.h"
#include "WildPokemon.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineRandom.h>

#include "PokemonEnum.h"
#include "PokemonStat.h"
#include "PokemonSkill.h"
#include "MyPokemon.h"


AWildPokemon::AWildPokemon()
{
    UEngineRandom Random;

    EWildPokemonEnum selectedPokemonEnum = static_cast<EWildPokemonEnum>(Random.RandomInt(0, 2));

    switch (selectedPokemonEnum)
    {
    case EWildPokemonEnum::Zigzagoon:
        Name = "ZIGZAGOON";
        break;
    case EWildPokemonEnum::Poochyena:
        Name = "POOCHYENA";
        break;
    case EWildPokemonEnum::Wurmple:
        Name = "WURMPLE";
        break;
    default:
        Name = "Unknown";
        break;
    }

    WildPokemonRender = CreateDefaultSubObject<USpriteRenderer>();
    WildPokemonRender->SetSprite(Name + ".png");
    WildPokemonRender->CreateAnimation(Name, Name + ".png", 0, 0, 0.2f);
    WildPokemonRender->ChangeAnimation(Name);
    WildPokemonRender->SetOrder(ERenderOrder::POKEMON);
    WildPokemonRender->SetSpriteScale(1.0f);

    bHasEncountered = false;
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
    return baseLevel + RegionRandom + regionLevel;
}

void AWildPokemon::SetPokemonStats(const std::string& PokemonName, int adjustedLevel)
{
    this->Name = PokemonName;
    this->Level = adjustedLevel;

    // 스탯 설정
    PokemonStats<ZigzagoonStats> stats(adjustedLevel); 
    this->HP = stats.GetHP();
    this->Attack = stats.GetAttack();
    this->Defense = stats.GetDefense();
    this->SpecialAttack = stats.GetSpecialAttack();
    this->SpecialDefense = stats.GetSpecialDefense();
    this->Speed = stats.GetSpeed();

    if (PokemonName == "ZIGZAGOON")
    {
        skill1 = "TACKLE";
        skill2 = "GROWL";
    }
    else if (PokemonName == "POOCHYENA")
    {
        skill1 = "TACKLE";
        skill2 = "HOWL";
    }
    else if (PokemonName == "WURMPLE")
    {
        skill1 = "TACKLE";
        skill2 = "STRINGSHOT";
    }
}

void AWildPokemon::EncounterWildPokemon(int regionLevel)
{
    if (bHasEncountered)
    {
        return;
    }

    UEngineRandom Random;

    int randomPokemonEnum = Random.RandomInt(static_cast<int>(EWildPokemonEnum::Zigzagoon), static_cast<int>(EWildPokemonEnum::Wurmple));
    EWildPokemonEnum selectedPokemonEnum = static_cast<EWildPokemonEnum>(randomPokemonEnum);

    int baseLevel = 1;
    int adjustedLevel = AdjustLevelByRegion(baseLevel, regionLevel);

    switch (selectedPokemonEnum)
    {
    case EWildPokemonEnum::Zigzagoon:
        SetPokemonStats("ZIGZAGOON", adjustedLevel);  // Zigzagoon일 경우
        break;
    case EWildPokemonEnum::Poochyena:
        SetPokemonStats("POOCHYENA", adjustedLevel);  // Poochyena일 경우
        break;
    case EWildPokemonEnum::Wurmple:
        SetPokemonStats("WURMPLE", adjustedLevel);  // Wurmple일 경우
        break;
    default:
        SetPokemonStats("UNKNOWN", adjustedLevel);  // 기본값
        break;
    }

    bHasEncountered = true;
}


void AWildPokemon::UseSkill(const std::string& skillName, class AMyPokemon* target)
{
    if (skillName == "POUND")
    {
        int damage = SkillHandler->Pound(Level, Attack, target->GetDefense());
        int TargetHp = target->GetHP();
        TargetHp -= damage;
        target->SetHP(TargetHp);
    }
    else if (skillName == "SCRATCH")
    {
        int damage = SkillHandler->Scratch(Level, Attack, target->GetDefense());
        int TargetHp = target->GetHP();
        TargetHp -= damage;
        target->SetHP(TargetHp);
    }
    else if (skillName == "TACKLE")
    {
        int damage = SkillHandler->Tackle(Level, Attack, target->GetDefense());
        int TargetHp = target->GetHP();
        TargetHp -= damage;
        target->SetHP(TargetHp);
    }
    else if (skillName == "LEER")
    {
        int targetDefense = target->GetDefense();
        SkillHandler->Leer(targetDefense);
        target->SetDefense(targetDefense);
    }
    else if (skillName == "GROWL")
    {
        int TargetAttack = target->GetAttack();
        SkillHandler->Growl(TargetAttack);
        target->SetAttack(TargetAttack);
    }
    else if (skillName == "Howl")
    {
        SkillHandler->Howl(Attack);
    }
    else if (skillName == "StringShot")
    {
        int targetSpeed = target->GetSpeed();
        SkillHandler->StringShot(targetSpeed);
        target->SetSpeed(targetSpeed);
    }
    else if (skillName == "-")
    {
        return;
    }
    else
    {
        return;
    }
}