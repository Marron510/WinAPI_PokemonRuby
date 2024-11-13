#pragma once


enum class ERenderOrder
{
	COLLISION = -100,
	WATER = -20,
	BACKGROUND = -10,
	Tile = 0,
	FLOWER = 10,
	PLAYER = 100,
	CURSOR = 200,
	FADE = 1000
};


//enum class EBackGroundCollision
//{
//	Player,
//	CollisionObject
//};