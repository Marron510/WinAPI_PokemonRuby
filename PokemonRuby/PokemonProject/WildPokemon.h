#pragma once
#include <EngineCore/Actor.h>
#include <vector>
#include <list>
#include <string>
#include <map>

enum class EWildPokemonEnum
{
    Zigzagoon,
    Poochyena,
    Wurmple,
    MAX
};

class AWildPokemon : public AActor
{
public:
    AWildPokemon();
    ~AWildPokemon();

    // delete function
    AWildPokemon(const AWildPokemon& _Other) = delete;
    AWildPokemon(AWildPokemon&& _Other) noexcept = delete;
    AWildPokemon& operator=(const AWildPokemon& _Other) = delete;
    AWildPokemon& operator=(AWildPokemon&& _Other) noexcept = delete;

    void BeginPlay() override;
    void Tick(float _DeltaTime) override;

    void EncounterWildPokemon(int regionLevel);

    std::string GetPokemonName() const { return Name; }
    int GetLevel() const { return Level; }
    int GetHP() const { return HP; }
    int GetAttack() const { return Attack; }
    int GetDefense() const { return Defense; }
    int GetSpecialAttack() const { return SpecialAttack; }
    int GetSpecialDefense() const { return SpecialDefense; }
    int GetSpeed() const { return Speed; }
    std::list<std::string> GetPokemonSkills() const { return Skills; }

    // Setters
    void SetPokemonName(const std::string& InName) { Name = InName; }
    void SetLevel(int InLevel) { Level = InLevel; }
    void SetHP(int InHP) { HP = InHP; }
    void SetAttack(int InAttack) { Attack = InAttack; }
    void SetDefense(int InDefense) { Defense = InDefense; }
    void SetSpecialAttack(int InSpecialAttack) { SpecialAttack = InSpecialAttack; }
    void SetSpecialDefense(int InSpecialDefense) { SpecialDefense = InSpecialDefense; }
    void SetSpeed(int InSpeed) { Speed = InSpeed; }
    void SetPokemonSkills(const std::list<std::string>& InSkills) { Skills = InSkills; }

protected:
    int AdjustLevelByRegion(int baseLevel, int regionLevel);

private:
    std::string Name;               // 포켓몬의 이름
    int Level;                      // 포켓몬의 레벨
    int HP;                         // HP
    int Attack;                     // 공격력
    int Defense;                    // 방어력
    int SpecialAttack;              // 특수 공격력
    int SpecialDefense;             // 특수 방어력
    int Speed;                      // 스피드

    std::list<std::string> Skills;  // 스킬 목록

    void SetPokemonStats(const std::string& PokemonName, int adjustedLevel);

    class USpriteRenderer* WildPokemonRender = nullptr;
    bool bHasEncountered = false;
};

