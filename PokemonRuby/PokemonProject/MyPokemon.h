#pragma once
#include <EngineCore/Actor.h>
#include <string>
#include <list>

class AMyPokemon : public AActor
{
public:

	enum class EMyPokemon
	{
		TREECKO,
		TORCHIC,
		MUDKIP,
		MAX
	};

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

    std::list<std::string> PKMSkills;

    USpriteRenderer* PokemonSprite;

	USpriteRenderer* MyPokemon;

};

