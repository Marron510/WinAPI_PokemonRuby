#include "PreCompile.h"
#include "PokemonMath.h"

FVector2D TileSize;

UPokemonMath::UPokemonMath()
{

}

UPokemonMath::~UPokemonMath()
{

}

FVector2D UPokemonMath::Lerp(const FVector2D& _Start, const FVector2D& _End, float _t)
{
	if (_t <= 0.0f)
	{
		return _Start;
	}

	if (_t >= 1.0f)
	{
		return _End;
	}

	return _Start * (1 - _t) + _End * _t;
}
