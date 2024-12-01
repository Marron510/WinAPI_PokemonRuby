#pragma once
#include <EngineBase/Object.h>

enum class ERenderOrder
{
	COLLISION = -100,
	WATER = -20,
	BACKGROUND = -10,
	Tile = 0,
	FLOWER = 10,
	TRUCK = 20,
	NPC = 40,
	PLAYER = 50,
	CHAT = 80,
	POKEMONSHADOW = 100,
	POKEMON = 300,
	SKILLEFFECT = 400,
	BackUI = 500,
	BackUI1 = 510,
	BackUI2 = 520,
	BackUI3 = 530,
	FONT = 600,
	CURSOR = 700,
	FADE = 1000
};

enum class ENPCDir
{
	LEFT_Left_Arm,
	LEFT_Right_Arm,
	RIGHT_Left_Arm,
	RIGHT_Right_Arm,
	UP_Left_Arm,
	UP_Right_Arm,
	DOWN_Left_Arm,
	DOWN_Right_Arm,
	MAX
};


class UPokemoncharacter : public UObject
{
public:
	UPokemoncharacter();
	~UPokemoncharacter();

	// delete Function
	UPokemoncharacter(const UPokemoncharacter& _Other) = delete;
	UPokemoncharacter(UPokemoncharacter&& _Other) noexcept = delete;
	UPokemoncharacter& operator=(const UPokemoncharacter& _Other) = delete;
	UPokemoncharacter& operator=(UPokemoncharacter&& _Other) noexcept = delete;


	enum class ECapitals
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		a,
		b,
		c,
		d,
		e,
		f,
		g,
		h,
		i,
		j,
		k,
		l,
		m,
		n,
		o,
		p,
		q,
		r,
		s,
		t,
		u,
		v,
		w,
		x,
		y,
		z,
		spacebar,
		comma,
		end,
		zero,
		one,
		two,
		three,
		four,
		five,
		six,
		seven,
		eight,
		nine,
		exclamation,
		question,
		men,
		women,
		slash,
		dotdot,
		doublequotationstart,
		doublequotationend,
		singlestart,
		singleend,
		bar,
		colon,
		END
	};
	

private:

};

