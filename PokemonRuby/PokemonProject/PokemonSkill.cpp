#include "PreCompile.h"
#include "PokemonSkill.h"


PokemonSkill::PokemonSkill()
{

}

PokemonSkill::~PokemonSkill()
{

}


int PokemonSkill::Pound(int level, int attack, int defense, bool isPhysical)
{
    int damage = (int)(((2 * level / 5 + 2) * attack * 40 / defense) / 50 + 2); // Pound는 파워 40
    return damage;
}

int PokemonSkill::Scratch(int level, int attack, int defense, bool isPhysical)
{
    int damage = (int)(((2 * level / 5 + 2) * attack * 40 / defense) / 50 + 2); // Scratch는 파워 40
    return damage;
}

int PokemonSkill::Tackle(int level, int attack, int defense, bool isPhysical)
{
    int damage = (int)(((2 * level / 5 + 2) * attack * 40 / defense) / 50 + 2);
    return damage;
}


void PokemonSkill::Leer(int& targetDefense)
{
    targetDefense -= 1; 
}

void PokemonSkill::Growl(int& targetAttack)
{
    targetAttack -= 1; 
}

void PokemonSkill::Howl(int& selfAttack)
{
    selfAttack += 1; 
}

void PokemonSkill::StringShot(int& targetSpeed)
{
    targetSpeed -= 1;
}