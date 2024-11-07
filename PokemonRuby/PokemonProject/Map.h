#pragma once
#include <EngineCore/Actor.h>

class AMap : public AActor
{
public:
	// 持失切 社瑚切
	AMap();
	~AMap();

	// delete funcion

	AMap(const AMap& _Other) = delete;
	AMap(AMap&& _Other) noexcept = delete;
	AMap& operator=(const AMap& _Other) = delete;
	AMap& operator=(AMap&& _Other) noexcept = delete;

	virtual FVector2D GetMapSize() = 0;
	


protected:

private:
	FVector2D MapSize;
};

