#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>
#include <string>
#include <vector>


class AMyPokemon;

class PokemonStateBackup 
{
public:
	void Backup(AMyPokemon& Pokemon);
	void Restore(AMyPokemon& Pokemon);

private:
	int Level, HP, MaxHp, Attack, Defense, SpecialAttack, SpecialDefense, Speed;
	std::string Name, Skill1, Skill2, Skill3, Skill4;
};


class PokemonStateManager
{
public:
	static PokemonStateManager& GetInstance();
	void SavePokemonState(AMyPokemon& Pokemon);
	void LoadPokemonState(AMyPokemon& Pokemon);
	PokemonStateBackup& GetSelectedPokemonState()
	{
		return PokemonState;
	}
private:
	PokemonStateBackup PokemonState;
};

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

	int GetLevel() const { return Level; }
	int GetHP() const { return HP; }
	int GetMaxHP() const { return MaxHp; }
	int GetAttack() const { return Attack; }
	int GetDefense() const { return Defense; }
	int GetSpecialAttack() const { return SpecialAttack; }
	int GetSpecialDefense() const { return SpecialDefense; }
	int GetSpeed() const { return Speed; }

	std::string GetMyPokemonName()
	{
		return Name;
	}


	void SetLevel(int InLevel) { Level = InLevel; }
	void SetHP(int InHP) { HP = InHP; }
	void SetMaxHP(int InHP) { MaxHp = InHP; }
	void SetAttack(int InAttack) { Attack = InAttack; }
	void SetDefense(int InDefense) { Defense = InDefense; }
	void SetSpecialAttack(int InSpecialAttack) { SpecialAttack = InSpecialAttack; }
	void SetSpecialDefense(int InSpecialDefense) { SpecialDefense = InSpecialDefense; }
	void SetSpeed(int InSpeed) { Speed = InSpeed; }

	void SetSkills(const std::string& skill1, const std::string& skill2,
		const std::string& skill3, const std::string& skill4)
	{
		this->skill1 = skill1;
		this->skill2 = skill2;
		this->skill3 = skill3;
		this->skill4 = skill4;
	}

	void SetPokemonName(const std::string& Name)
	{
		this->Name = Name;
	}


	void AddEXP(int GainedEXP);
	void UseSkill(const std::string& skillName, class AWildPokemon* target);
	void MovePokemonForSkill();

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
	std::string GetLevelStirng()
	{
		return LevelString;
	}
	int GetEXP()
	{
		return CurrentEXP;
	}
	int GetMaxEXP()
	{
		return MaxEXP;
	}
	int GetPP(int skillIndex)
	{
		return PP[skillIndex];
	}
	int GetMaxPP(int skillIndex)
	{
		return MaxPP[skillIndex];
	}

	void BackupState()
	{
		StateBackup->Backup(*this);
	}

	void RestoreState()
	{
		StateBackup->Restore(*this);
	}



protected:

private:

	std::string Name;
	std::string LevelString;

	
	int Level = 5;
	int HP = 40;
	int MaxHp = 40;
	int Attack = 180;
	int Defense = 35;
	int SpecialAttack = 65;
	int SpecialDefense = 50;
	int Speed = 70;
	int CurrentEXP = 0;
	int MaxEXP = 50;
	std::string skill1, skill2, skill3, skill4;
	std::vector<int> PP;
	std::vector<int> MaxPP;
	class USpriteRenderer* MyPokemon;

	class PokemonSkill* SkillHandler;


	FVector2D StartPosition;
	FVector2D TargetPosition;
	FVector2D CurrentVelocity;
	bool bIsMovingRight;
	bool bIsSkillActive;
	class USoundPlayer BGMPlayer;


	PokemonStateBackup* StateBackup;
};

