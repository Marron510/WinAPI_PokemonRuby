#pragma once

class PokemonSkill
{
public:
	enum class ETREEKOSKILL
	{
		Pound,        // 1레벨
		Leer,         // 6레벨
		Absorb,       // 11레벨
		QuickAttack,  // 16레벨
		Agility,      // 21레벨
		LeafBlade,    // 26레벨
		Slam,         // 31레벨
		EnergyBall    // 36레벨
	};

	enum class EZIGZAGOONSKILL
	{
		Tackle,       // 1레벨
		Growl,        // 1레벨
		QuickAttack,  // 6레벨
		TailWhip,     // 9레벨
		Headbutt,     // 15레벨
		Rest,         // 23레벨
		Snore,        // 23레벨
		HyperBeam     // 55레벨
	};

	// 생성자 소멸자
	PokemonSkill();
	~PokemonSkill();

	// delete funcion

	PokemonSkill(const PokemonSkill& _Other) = delete;
	PokemonSkill(PokemonSkill&& _Other) noexcept = delete;
	PokemonSkill& operator=(const PokemonSkill& _Other) = delete;
	PokemonSkill& operator=(PokemonSkill&& _Other) noexcept = delete;


	static int CalculateDamage(int level, int attack, int defense, int power, bool isPhysical, float effectiveness);
	static void GetSkillInfo(ETREEKOSKILL skill, int& level, int& attack, int& defense, int& power, bool& isPhysical, float& effectiveness);


protected:

private:

};

