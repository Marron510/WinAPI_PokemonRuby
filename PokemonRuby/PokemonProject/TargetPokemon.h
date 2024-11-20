#pragma once

#include <string.h>


class ATargetPokemon 
{
public:
	// 생성자 소멸자
	ATargetPokemon();
	~ATargetPokemon();

	// delete funcion

	ATargetPokemon(const ATargetPokemon& _Other) = delete;
	ATargetPokemon(ATargetPokemon&& _Other) noexcept = delete;
	ATargetPokemon& operator=(const ATargetPokemon& _Other) = delete;
	ATargetPokemon& operator=(ATargetPokemon&& _Other) noexcept = delete;

    


    std::string GetName() const
    {
        return Name;
    }
   
    int GetLevel() const
    { 
        return Level; 
    }
   
    int GetHP() const 
    {
        return HP; 
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

    // Setter 함수들
    void SetName(const std::string& InName)
    {
        Name = InName;
    }
    void SetLevel(int InLevel) 
    {
        Level = InLevel;
    }
    void SetHP(int InHP)
    {
        HP = InHP;
    }
    void SetAttack(int InAttack) 
    { 
        Attack = InAttack; 
    }
    void SetDefense(int InDefense)
    {
        Defense = InDefense;
    }
    void SetSpecialAttack(int InSpecialAttack)
    {
        SpecialAttack = InSpecialAttack; 
    }
    void SetSpecialDefense(int InSpecialDefense)
    {
        SpecialDefense = InSpecialDefense;
    }
    void SetSpeed(int InSpeed)
    {
        Speed = InSpeed;
    }

protected:

private:
  
    std::string Name;              // 포켓몬의 이름
    int Level;                     // 포켓몬의 레벨
    int HP;                        // HP
    int Attack;                    // 공격력
    int Defense;                   // 방어력
    int SpecialAttack;             // 특수 공격력
    int SpecialDefense;            // 특수 방어력
    int Speed;                     // 스피드
};

