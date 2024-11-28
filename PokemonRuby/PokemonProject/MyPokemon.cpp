#include "PreCompile.h"
#include "MyPokemon.h"


#include <EngineCore/SpriteRenderer.h>

#include  "WildPokemon.h"
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
        break;
    case EMyPokemon::TORCHIC:
        MyPokemon->SetSprite("Torchic.png");
        Name = "TORCHIC";
        skill1 = "SCRATCH";
        skill2 = "LEER";
        skill3 = "-";
        skill4 = "-";
        break;
    case EMyPokemon::MUDKIP:
        MyPokemon->SetSprite("Mudkip.png");
        Name = "MUDKIP";
        skill1 = "TACKLE";
        skill2 = "LEER";
        skill3 = "-";
        skill4 = "-";
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
    if (skillName == "POUND" || skillName == "SCRATCH" || skillName == "TACKLE")
    {
        MovePokemonForSkill();

        int damage = 0;
        if (skillName == "POUND")
        {
            damage = SkillHandler->Pound(Level, Attack, target->GetDefense());
        }
        else if (skillName == "SCRATCH")
        {
            damage = SkillHandler->Scratch(Level, Attack, target->GetDefense());
        }
        else if (skillName == "TACKLE")
        {
            damage = SkillHandler->Tackle(Level, Attack, target->GetDefense());
        }

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
