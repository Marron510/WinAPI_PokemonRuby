#include "PreCompile.h"
#include "MyPokemon.h"


#include <EngineCore/SpriteRenderer.h>

#include "WildPokemon.h"
#include "PokemonEnum.h"
#include "PokemonSkill.h"
#include "MyPokemon.h"

AMyPokemon::AMyPokemon()
{
    MyPokemon = CreateDefaultSubObject<USpriteRenderer>();
    SetPokemon(EMyPokemon::TORCHIC);
    MyPokemon->SetOrder(ERenderOrder::POKEMON);
    MyPokemon->SetSpriteScale(1.0f);
    LevelString = std::to_string(Level);
}

AMyPokemon::~AMyPokemon()
{
}

void AMyPokemon::BeginPlay()
{
    Super::BeginPlay();
    
}

void AMyPokemon::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    if (bIsSkillActive)
    {
        FVector2D currentPosition = MyPokemon->GetComponentLocation();

        if (bIsMovingRight)
        {
            currentPosition += CurrentVelocity; 

            if ((currentPosition.X >= TargetPosition.X))
            {
                currentPosition = TargetPosition; 
                bIsMovingRight = false;  
            }
        }
        else
        {
            currentPosition -= CurrentVelocity; 

            if ((currentPosition.X <= StartPosition.X))
            {
                currentPosition = StartPosition; 
                bIsMovingRight = true;  
                bIsSkillActive = false; 
            }
        }

        MyPokemon->SetComponentLocation(currentPosition);
    }
}


void AMyPokemon::SetPokemon(EMyPokemon PokemonType)
{
    switch (PokemonType)
    {
    case EMyPokemon::TREECKO:
        MyPokemon->SetSprite("Treecko.png");
        Name = "TREECKO";
        skill1 = "POUND";
        skill2 = "LEER";
        skill3 = "-";
        skill4 = "-";

        PP = { 35, 30, 0, 0 };    
        MaxPP = { 35, 30, 0, 0 }; 
        break;

    case EMyPokemon::TORCHIC:
        MyPokemon->SetSprite("Torchic.png");
        Name = "TORCHIC";
        skill1 = "SCRATCH";
        skill2 = "LEER";
        skill3 = "-";
        skill4 = "-";

        PP = { 35, 30, 0, 0 };
        MaxPP = { 35, 30, 0, 0 };
        break;

    case EMyPokemon::MUDKIP:
        MyPokemon->SetSprite("Mudkip.png");
        Name = "MUDKIP";
        skill1 = "TACKLE";
        skill2 = "LEER";
        skill3 = "-";
        skill4 = "-";

        PP = { 35, 30, 0, 0 };
        MaxPP = { 35, 30, 0, 0 };
        break;

    default:
        break;
    }

    InitializePokemonAttributes(PokemonType);
}


void AMyPokemon::InitializePokemonAttributes(EMyPokemon PokemonType)
{
    switch (PokemonType)
    {
    case EMyPokemon::TREECKO:
        Level = 5;
        HP = 40;
        MaxHp = 40;
        Attack = 180;
        Defense = 35;
        SpecialAttack = 65;
        SpecialDefense = 50;
        Speed = 70;
        break;
    case EMyPokemon::TORCHIC:
        Level = 5;
        HP = 40;
        MaxHp = 40;
        Attack = 200;
        Defense = 40;
        SpecialAttack = 70;
        SpecialDefense = 50;
        Speed = 45;
        break;
    case EMyPokemon::MUDKIP:
        Level = 5;
        HP = 50;
        MaxHp = 50;
        Attack = 200;
        Defense = 50;
        SpecialAttack = 44;
        SpecialDefense = 50;
        Speed = 40;
        break;
    default:
        break;
    }
}

void AMyPokemon::UseSkill(const std::string& skillName, AWildPokemon* target)
{
    int skillIndex = -1;

    if (skillName == skill1)
        skillIndex = 0;
    else if (skillName == skill2)
        skillIndex = 1;
    else if (skillName == skill3)
        skillIndex = 2;
    else if (skillName == skill4)
        skillIndex = 3;


    PP[skillIndex]--;

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
    else if (skillName == "-")
    {
        return;
    }
}

void AMyPokemon::MovePokemonForSkill()
{
    if (!bIsSkillActive)
    {
        StartPosition = MyPokemon->GetComponentLocation();  
        TargetPosition = StartPosition + FVector2D(50.0f, 0.0f); 
        CurrentVelocity = FVector2D::RIGHT; 
        bIsMovingRight = true;
        bIsSkillActive = true;  
    }
}


void AMyPokemon::AddEXP(int GainedEXP)
{
    CurrentEXP = UEngineMath::Clamp(CurrentEXP + GainedEXP, 0, MaxEXP);
}


void PokemonStateBackup::Backup(AMyPokemon& Pokemon)
{
    Level = Pokemon.GetLevel();
    HP = Pokemon.GetHP();
    MaxHp = Pokemon.GetMaxHP();
    Attack = Pokemon.GetAttack();
    Defense = Pokemon.GetDefense();
    SpecialAttack = Pokemon.GetSpecialAttack();
    SpecialDefense = Pokemon.GetSpecialDefense();
    Speed = Pokemon.GetSpeed();
    Name = Pokemon.GetName();
    Skill1 = Pokemon.GetSkill1();
    Skill2 = Pokemon.GetSkill2();
    Skill3 = Pokemon.GetSkill3();
    Skill4 = Pokemon.GetSkill4();
}

void PokemonStateBackup::Restore(AMyPokemon& Pokemon) {
    Pokemon.SetLevel(Level);
    Pokemon.SetHP(HP);
    Pokemon.SetMaxHP(MaxHp);
    Pokemon.SetAttack(Attack);
    Pokemon.SetDefense(Defense);
    Pokemon.SetSpecialAttack(SpecialAttack);
    Pokemon.SetSpecialDefense(SpecialDefense);
    Pokemon.SetSpeed(Speed);
    Pokemon.SetPokemonName(Name);
    Pokemon.SetSkills(Skill1, Skill2, Skill3, Skill4);
}


PokemonStateManager& PokemonStateManager::GetInstance() 
{
    static PokemonStateManager Instance;
    return Instance;
}

void PokemonStateManager::SavePokemonState(AMyPokemon& Pokemon)
{
    PokemonState.Backup(Pokemon);
}

void PokemonStateManager::LoadPokemonState(AMyPokemon& Pokemon)
{
    PokemonState.Restore(Pokemon);
}
