#pragma once
class PokemonMath
{
public:
	// 持失切 社瑚切
	PokemonMath();
	~PokemonMath();

	// delete funcion

	PokemonMath(const PokemonMath& _Other) = delete;
	PokemonMath(PokemonMath&& _Other) noexcept = delete;
	PokemonMath& operator=(const PokemonMath& _Other) = delete;
	PokemonMath& operator=(PokemonMath&& _Other) noexcept = delete;

	void Lerp(FVector2D _Start, FVector2D _End, float _t);
	FVector2D ToTileFvector2D(FVector2D _Value);

protected:

private:
	static FVector2D TileSize;
};

