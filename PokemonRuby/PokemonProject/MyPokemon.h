#pragma once
#include <EngineCore/Actor.h>
#include <string>
#include <list>

class AMyPokemon : public AActor
{
public:
	// 생성자 소멸자
	AMyPokemon();
	~AMyPokemon();

	// delete funcion

	AMyPokemon(const AMyPokemon& _Other) = delete;
	AMyPokemon(AMyPokemon&& _Other) noexcept = delete;
	AMyPokemon& operator=(const AMyPokemon& _Other) = delete;
	AMyPokemon& operator=(AMyPokemon&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	void LevelUp(int levels = 1);


protected:

private:

    std::string PKMName;

    int MaxHP = 100;
    int PHp = 0;
    int PAtk = 0;
    int PDef = 0;
    int Pspeed = 0;
    int PSpAtk = 0;
    int PSpDef = 0;

    int BaseStat = 0;
    int IValue = 0;
    int EVs = 0;
    int Lv = 0; 
    int Nature = 0;

    // 포켓몬 기술
    std::list<std::string> PKMSkills;

    // 스프라이트 렌더러 (Treecko 등 포켓몬 스프라이트)
    USpriteRenderer* PokemonSprite;

    // 능력치 계산 함수
    void UpdateStats();

    // 데미지 계산 함수
    static int CalculateDamage(int level, int attack, int defense, int basePower, bool isPhysical, float effectiveness);

	USpriteRenderer* Treecko;

};

