#pragma once
#include <EngineCore/Actor.h>
#include <string>
#include <list>

class APokemon : public AActor
{
public:
	// 생성자 소멸자
	APokemon();
	~APokemon();

	// delete funcion

	APokemon(const APokemon& _Other) = delete;
	APokemon(APokemon&& _Other) noexcept = delete;
	APokemon& operator=(const APokemon& _Other) = delete;
	APokemon& operator=(APokemon&& _Other) noexcept = delete;

	
	int WildPokemonHp() // 야생포켓몬 Hp
	{
		return ((BaseStat * 2) + IValue + (EVs / 4)) * (Lv / 100) + (5 * Nature);
	}
	
	int WildPokemon() // 야생포켓몬 Hp
	{
		return ((BaseStat * 2) + IValue + (EVs / 4)) * (Lv / 100) + (5 * Nature);
	}



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
	



};

