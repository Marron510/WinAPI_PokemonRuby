#pragma once
#include <EngineBase/EngineMath.h>



class UPokemonMath 
{
public:
	// 持失切 社瑚切
	UPokemonMath();
	~UPokemonMath();

	// delete funcion

	UPokemonMath(const UPokemonMath& _Other) = delete;
	UPokemonMath(UPokemonMath&& _Other) noexcept = delete;
	UPokemonMath& operator=(const UPokemonMath& _Other) = delete;
	UPokemonMath& operator=(UPokemonMath&& _Other) noexcept = delete;

	
	FVector2D Lerp(const FVector2D& _Start, const FVector2D& _End, float _t);




protected:

private:
	static FVector2D TileSize;
};

