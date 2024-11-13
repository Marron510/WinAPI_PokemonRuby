#pragma once
#include <EngineCore/Actor.h>

class Combat : public AActor
{
public:
	// 持失切 社瑚切
	Combat();
	~Combat();

	// delete funcion

	Combat(const Combat& _Other) = delete;
	Combat(Combat&& _Other) noexcept = delete;
	Combat& operator=(const Combat& _Other) = delete;
	Combat& operator=(Combat&& _Other) noexcept = delete;


protected:

private:

};

