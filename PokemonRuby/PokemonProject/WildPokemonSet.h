#pragma once
class WildPokemonSet
{
public:
	// 持失切 社瑚切
	WildPokemonSet();
	~WildPokemonSet();

	// delete funcion

	WildPokemonSet(const WildPokemonSet& _Other) = delete;
	WildPokemonSet(WildPokemonSet&& _Other) noexcept = delete;
	WildPokemonSet& operator=(const WildPokemonSet& _Other) = delete;
	WildPokemonSet& operator=(WildPokemonSet&& _Other) noexcept = delete;


protected:

private:

};

