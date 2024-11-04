#pragma once
#include <EngineCore/Actor.h>

class ALittleRootTownMap : public AActor
{
public:
	// 持失切 社瑚切
	ALittleRootTownMap();
	~ALittleRootTownMap();

	// delete funcion

	ALittleRootTownMap(const ALittleRootTownMap& _Other) = delete;
	ALittleRootTownMap(ALittleRootTownMap&& _Other) noexcept = delete;
	ALittleRootTownMap& operator=(const ALittleRootTownMap& _Other) = delete;
	ALittleRootTownMap& operator=(ALittleRootTownMap&& _Other) noexcept = delete;


protected:

private:

};

