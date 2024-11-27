#pragma once
class SelectPokemonMode
{
public:
	// 持失切 社瑚切
	SelectPokemonMode();
	~SelectPokemonMode();

	// delete funcion

	SelectPokemonMode(const SelectPokemonMode& _Other) = delete;
	SelectPokemonMode(SelectPokemonMode&& _Other) noexcept = delete;
	SelectPokemonMode& operator=(const SelectPokemonMode& _Other) = delete;
	SelectPokemonMode& operator=(SelectPokemonMode&& _Other) noexcept = delete;


protected:

private:

};

