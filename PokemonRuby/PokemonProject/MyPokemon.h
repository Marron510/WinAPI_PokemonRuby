#pragma once
#include <EngineCore/Actor.h>
#include <string>
#include <vector>

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



	// 持失切 社瑚切
	AMyPokemon();
	~AMyPokemon();

	// delete funcion

	AMyPokemon(const AMyPokemon& _Other) = delete;
	AMyPokemon(AMyPokemon&& _Other) noexcept = delete;
	AMyPokemon& operator=(const AMyPokemon& _Other) = delete;
	AMyPokemon& operator=(AMyPokemon&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetPokemon(EMyPokemon PokemonType);
	void InitializePokemonAttributes(EMyPokemon PokemonType);
	

	std::string GetMyPokemonName()
	{
		return Name;
	}

	void UseSkill(const std::string& skillName, class AWildPokemon* target);

	std::string GetSkill1()
	{
		return skill1;
	}
	std::string GetSkill2()
	{
		return skill2;
	}
	std::string GetSkill3()
	{
		return skill3;
	}
	std::string GetSkill4()
	{
		return skill4;
	}

protected:

private:

    std::string Name;              

    int Level;                     
    int HP;                        
    int Attack;                    
    int Defense;                   
    int SpecialAttack;             
    int SpecialDefense;            
    int Speed;                     

	
	std::string skill1, skill2, skill3, skill4;

    class USpriteRenderer* PokemonSprite;

	class USpriteRenderer* MyPokemon;

	class PokemonSkill* SkillHandler;

};

