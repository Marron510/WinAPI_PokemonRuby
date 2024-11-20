#include "PreCompile.h"
#include "PokemonSkill.h"


PokemonSkill::PokemonSkill()
{

}

PokemonSkill::~PokemonSkill()
{

}


int PokemonSkill::CalculateDamage(int level, int attack, int defense, int power, bool isPhysical, float effectiveness)
{
    float damage;
    if (isPhysical)
    {
        // 물리 공격 공식
        damage = ((2 * level + 10) / 250.0f) * (static_cast<float>(attack) / defense) * power + 2;
    }
    else
    {
        // 특수 공격 공식
        damage = ((2 * level + 10) / 250.0f) * (static_cast<float>(attack) / defense) * power + 2;
    }

    damage *= effectiveness;
 
    if (damage < 1)
    {
        return 1;
    }

    return static_cast<int>(damage);
}




void PokemonSkill::GetSkillInfo(ETREEKOSKILL skill, int& level, int& attack, int& defense, int& power, bool& isPhysical, float& effectiveness)
{
    switch (skill)
    {
    case ETREEKOSKILL::Pound:
        level = 15;    
        attack = 30;   
        defense = 20;  
        power = 40;    
        isPhysical = true; 
        effectiveness = 1.0f; 
        break;
    case ETREEKOSKILL::Leer:
        level = 6;
        attack = 0;
        defense = 0;
        power = 0;
        isPhysical = false;
        effectiveness = 1.0f;
        break;
    case ETREEKOSKILL::Absorb:
        level = 11;
        attack = 30;
        defense = 20;
        power = 20; // Absorb의 위력
        isPhysical = false;
        effectiveness = 1.0f;
        break;
    case ETREEKOSKILL::QuickAttack:
        level = 16;
        attack = 40;
        defense = 20;
        power = 40; // QuickAttack의 위력
        isPhysical = true;
        effectiveness = 1.0f;
        break;
    case ETREEKOSKILL::Agility:
        level = 21;
        attack = 0;
        defense = 0;
        power = 0;
        isPhysical = false;
        effectiveness = 1.0f;
        break;
    case ETREEKOSKILL::LeafBlade:
        level = 26;
        attack = 50;
        defense = 20;
        power = 70; // LeafBlade의 위력
        isPhysical = true;
        effectiveness = 2.0f; // 풀 타입이 물타입에 강함
        break;
    case ETREEKOSKILL::Slam:
        level = 31;
        attack = 60;
        defense = 25;
        power = 80; // Slam의 위력
        isPhysical = true;
        effectiveness = 1.0f;
        break;
    case ETREEKOSKILL::EnergyBall:
        level = 36;
        attack = 60;
        defense = 30;
        power = 90; // EnergyBall의 위력
        isPhysical = false;
        effectiveness = 1.0f;
        break;
    default:
        level = 0;
        attack = 0;
        defense = 0;
        power = 0;
        isPhysical = false;
        effectiveness = 1.0f;
        break;
    }
}