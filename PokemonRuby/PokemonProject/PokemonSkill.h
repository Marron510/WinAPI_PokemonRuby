#pragma once

class PokemonSkill
{
public:
	enum class ETREEKOSKILL
	{
		Pound,
		Glare,
		Leafage,
		QuickAttack
	};


	// 持失切 社瑚切
	PokemonSkill();
	~PokemonSkill();

	// delete funcion

	PokemonSkill(const PokemonSkill& _Other) = delete;
	PokemonSkill(PokemonSkill&& _Other) noexcept = delete;
	PokemonSkill& operator=(const PokemonSkill& _Other) = delete;
	PokemonSkill& operator=(PokemonSkill&& _Other) noexcept = delete;


protected:

private:

};

