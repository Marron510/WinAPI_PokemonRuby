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




	//
	//int WildPokemonHp() // 야생포켓몬 Hp
	//{
	//	return ((BaseStat * 2) + IValue + (EVs / 4)) * (Lv / 100) + (5 * Nature);
	//}
	//
	//int WildPokemon() // 야생포켓몬 Hp
	//{
	//	return ((BaseStat * 2) + IValue + (EVs / 4)) * (Lv / 100) + (5 * Nature);
	//}



protected:

private:

	std::string PKMName;
	int PHp = 0;
	int PAtk = 0;
	int PDef = 0;
	int Pspeed = 0;
	int PSpAtk = 0;
	int PSpDef = 0;
	
	std::list<int> PKMData;

	int BaseStat = 0; // 종족값
	int IValue = 0; // 개체값
	int EVs = 0; // 노력치
	int Lv = 0;
	int Nature = 0; // 성격
	

	USpriteRenderer* Treecko;

};

