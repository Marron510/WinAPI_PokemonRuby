#pragma once


enum class ERenderOrder
{
	COLLISION = -100,
	WATER = -20,
	BACKGROUND = -10,
	Tile = 0,
	FLOWER = 10,
	PLAYER = 100,
	POKEMONSHADOW = 250,
	POKEMON = 300,
	UI = 400,
	CURSOR = 500,
	SKILLEFFECT = 350,
	FADE = 1000
};


//enum class EBackGroundCollision
//{
//	Player,
//	CollisionObject
//};