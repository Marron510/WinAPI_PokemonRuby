#pragma once


template <typename PokemonName>
class PokemonStats
{
public:
    PokemonStats(int level)
        : Level(level)
    {
        MaxHP = PokemonName::BaseHP + (level * PokemonName::HPPerLevel);
        HP = MaxHP;
        Attack = PokemonName::BaseAttack + (level * PokemonName::AttackPerLevel);
        Defense = PokemonName::BaseDefense + (level * PokemonName::DefensePerLevel);
        SpecialAttack = PokemonName::BaseSpecialAttack + (level * PokemonName::SpecialAttackPerLevel);
        SpecialDefense = PokemonName::BaseSpecialDefense + (level * PokemonName::SpecialDefensePerLevel);
        Speed = PokemonName::BaseSpeed + (level * PokemonName::SpeedPerLevel);
    }

    int GetHP() const
    {
        return HP;
    }

    int GetMaxHP() const
    {
        return MaxHP;
    }

    int GetAttack() const
    {
        return Attack;
    }

    int GetDefense() const
    {
        return Defense;
    }

    int GetSpecialAttack() const
    {
        return SpecialAttack;
    }

    int GetSpecialDefense() const
    {
        return SpecialDefense;
    }

    int GetSpeed() const
    {
        return Speed;
    }


protected:
   

private:
    int Level = 1;
    int HP = 10;
    int MaxHP = 10;
    int Attack = 1;
    int Defense = 1;
    int SpecialAttack = 1;
    int SpecialDefense = 1;
    int Speed = 1;

};



class ZigzagoonStats : public PokemonStats<ZigzagoonStats>
{
public:
    ZigzagoonStats(int level) : PokemonStats(level) {}

    static const int BaseHP = 38;
    static const int BaseAttack = 30;
    static const int BaseDefense = 41;
    static const int BaseSpecialAttack = 30;
    static const int BaseSpecialDefense = 41;
    static const int BaseSpeed = 60;
    
    static const int HPPerLevel = 2;
    static const int AttackPerLevel = 1;
    static const int DefensePerLevel = 1;
    static const int SpecialAttackPerLevel = 1;
    static const int SpecialDefensePerLevel = 1;
    static const int SpeedPerLevel = 1;
   
};

class PoochyenaStats : public PokemonStats<PoochyenaStats>
{
public:
    PoochyenaStats(int level) : PokemonStats(level) {}


    static const int BaseHP = 45;
    static const int BaseAttack = 55;
    static const int BaseDefense = 35;
    static const int BaseSpecialAttack = 30;
    static const int BaseSpecialDefense = 30;
    static const int BaseSpeed = 35;

    static const int HPPerLevel = 2;
    static const int AttackPerLevel = 1;
    static const int DefensePerLevel = 1;
    static const int SpecialAttackPerLevel = 1;
    static const int SpecialDefensePerLevel = 1;
    static const int SpeedPerLevel = 1;
    
};

class WurmpleStats : public PokemonStats<WurmpleStats>
{
public:
    WurmpleStats(int level) : PokemonStats(level) {}

    static const int BaseHP = 45;
    static const int BaseAttack = 45;
    static const int BaseDefense = 35;
    static const int BaseSpecialAttack = 20;
    static const int BaseSpecialDefense = 30;
    static const int BaseSpeed = 20;

    static const int HPPerLevel = 2;
    static const int AttackPerLevel = 1;
    static const int DefensePerLevel = 1;
    static const int SpecialAttackPerLevel = 1;
    static const int SpecialDefensePerLevel = 1;
    static const int SpeedPerLevel = 1;
    
};


