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
    if (IsSkillActive)
    {
        FVector2D currentPosition = WildPokemonRender->GetComponentLocation();

        if (IsMovingLeft)
        {
            currentPosition += CurrentVelocity;

            if ((currentPosition.X <= TargetPosition.X))
            {
                currentPosition = TargetPosition;
                IsMovingLeft = false;
            }
        }
        else
        {
            currentPosition -= CurrentVelocity;

            if ((currentPosition.X >= StartPosition.X))
            {
                currentPosition = StartPosition;
                IsMovingLeft = true;
                IsSkillActive = false;
            }
        }

        WildPokemonRender->SetComponentLocation(currentPosition);
    }
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
    LevelString = std::to_string(Level);
    PokemonStats<ZigzagoonStats> stats(adjustedLevel); 
    this->HP = stats.GetHP();
    this->MaxHP = stats.GetMaxHP();
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

    LevelString = std::to_string(Level);

    UEngineRandom Random;

    int randomPokemonEnum = Random.RandomInt(static_cast<int>(EWildPokemonEnum::Zigzagoon), static_cast<int>(EWildPokemonEnum::Wurmple));
    EWildPokemonEnum selectedPokemonEnum = static_cast<EWildPokemonEnum>(randomPokemonEnum);

    int baseLevel = 1;
    int adjustedLevel = AdjustLevelByRegion(baseLevel, regionLevel);

    switch (selectedPokemonEnum)
    {
    case EWildPokemonEnum::Zigzagoon:
        SetPokemonStats("ZIGZAGOON", adjustedLevel);  // Zigzagoon老 版快
        break;
    case EWildPokemonEnum::Poochyena:
        SetPokemonStats("POOCHYENA", adjustedLevel);  // Poochyena老 版快
        break;
    case EWildPokemonEnum::Wurmple:
        SetPokemonStats("WURMPLE", adjustedLevel);  // Wurmple老 版快
        break;
    default:
        SetPokemonStats("UNKNOWN", adjustedLevel);  // 扁夯蔼
        break;
    }

    bHasEncountered = true;
}


void AWildPokemon::UseSkill(const std::string& skillName, class AMyPokemon* target)
{

    if (skillName == "POUND" || skillName == "SCRATCH" || skillName == "TACKLE")
    {
        MovePokemonForSkill();

        int damage = 0;
        if (skillName == "POUND")
        {
            BGMPlayer = UEngineSound::Play("SKILL_Pound.mp3");
            damage = SkillHandler->Pound(Level, Attack, target->GetDefense());
        }
        else if (skillName == "SCRATCH")
        {
            BGMPlayer = UEngineSound::Play("SKILL_Scratch.mp3");
            damage = SkillHandler->Scratch(Level, Attack, target->GetDefense());
        }
        else if (skillName == "TACKLE")
        {
            BGMPlayer = UEngineSound::Play("SKILL_Tackle.mp3");
            damage = SkillHandler->Tackle(Level, Attack, target->GetDefense());
        }

        int TargetHp = target->GetHP();
        TargetHp -= damage;
        target->SetHP(TargetHp);
    }
    else if (skillName == "LEER")
    {
        int targetDefense = target->GetDefense();
        BGMPlayer = UEngineSound::Play("SKILL_Leer.mp3");
        SkillHandler->Leer(targetDefense);
        target->SetDefense(targetDefense);
    }
    else if (skillName == "GROWL")
    {
        int TargetAttack = target->GetAttack();
        BGMPlayer = UEngineSound::Play("SKILL_Growl.mp3");
        SkillHandler->Growl(TargetAttack);
        target->SetAttack(TargetAttack);
    }
    else if (skillName == "Howl")
    {
        SkillHandler->Howl(Attack);
        BGMPlayer = UEngineSound::Play("SKILL_Howl.mp3");
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



void AWildPokemon::MovePokemonForSkill()
{
    if (!IsSkillActive)
    {
        StartPosition = WildPokemonRender->GetComponentLocation();
        TargetPosition = StartPosition + FVector2D(-50.0f, 0.0f);
        CurrentVelocity = FVector2D::LEFT;
        IsMovingLeft = true;
        IsSkillActive = true;
    }
}

