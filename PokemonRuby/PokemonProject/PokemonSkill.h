#pragma once

class PokemonSkill
{
public:
	enum class ETREEKOSKILL
	{
		Pound,        // 1레벨: 물리 공격, 일반 타입
		Leer,         // 1레벨: 상대의 방어력 1단계 감소      
	};

	enum class ETORCHICSKILL
	{
		Scratch,      // 1레벨: 물리 공격, 일반 타입
		Leer,         // 1레벨: 상대의 방어력 1단계 감소
	};

	enum class EMUDKIPSKILL
	{
		Tackle,       // 1레벨: 물리 공격, 노말 타입
		Leer,         // 1레벨: 상대의 방어력 1단계 감소
	};

	//-------------------------

	enum class EZIGZAGOONSKILL
	{
		Tackle,       // 1레벨: 물리 공격, 노말 타입
		Growl,        // 1레벨: 상대의 공격력 1단계 감소
	};

	enum class EPOOCHYENASKILL
	{
		Tackle,       // 1레벨: 물리 공격, 노말 타입
		Howl,         // 1레벨: 자신의 공격력 1단계 증가
	};

	enum class EWURMPLESKILL
	{
		Tackle,       // 1레벨: 물리 공격, 노말 타입
		StringShot,   // 1레벨: 상대의 스피드 1단계 감소
	};

	//-------------------------
	

	// 생성자 소멸자
	PokemonSkill();
	~PokemonSkill();

	// delete funcion

	PokemonSkill(const PokemonSkill& _Other) = delete;
	PokemonSkill(PokemonSkill&& _Other) noexcept = delete;
	PokemonSkill& operator=(const PokemonSkill& _Other) = delete;
	PokemonSkill& operator=(PokemonSkill&& _Other) noexcept = delete;


	// 물리 공격 스킬들
	int Pound(int level, int attack, int defense, bool isPhysical = true);
	int Scratch(int level, int attack, int defense, bool isPhysical = true);
	int Tackle(int level, int attack, int defense, bool isPhysical = true);

	// 상태 변화 스킬들
	void Leer(int& targetDefense);  // 방어력 감소
	void Growl(int& targetAttack);  // 공격력 감소
	void Howl(int& selfAttack);    // 자신의 공격력 증가
	void StringShot(int& targetSpeed); // 상대 스피드 감소

protected:

private:

};

