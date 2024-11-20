#pragma once
#include <EngineCore/Actor.h>
#include "TargetPokemon.h"

#include <vector>
#include <map>

enum class EWildPokemonEnum
{
    Zigzagoon,
    Poochyena,
    Wurmple,
    // 추가 포켓몬은 여기에 추가
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

    // 랜덤 포켓몬 인카운터
    void EncounterWildPokemon(int regionLevel);

protected:


private:
    // 지역에 따라 레벨 조정하는 함수
    int AdjustLevelByRegion(int baseLevel, int regionLevel);

    std::map<EWildPokemonEnum, std::vector<ATargetPokemon>> WildPokemons;
    class USpriteRenderer* WildPokemonRender = nullptr;
    ATargetPokemon* EncounteredPokemon = nullptr;


};
