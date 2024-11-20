#include "PreCompile.h"
#include "PokemonSkill.h"


PokemonSkill::PokemonSkill()
{

}

PokemonSkill::~PokemonSkill()
{

}


static int CalculateDamage(int level, int attack, int defense, int power, bool isPhysical, float effectiveness)
{
    // 물리 공격인지 특수 공격인지를 구분하여 계산
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

    // 상성 적용 (효과적인 경우 더 많은 데미지, 효과가 없는 경우 데미지 감소)
    damage *= effectiveness;

    // 최소 데미지는 1로 설정
   // return std::max(1, static_cast<int>(damage));
}