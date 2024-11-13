#pragma once
#include <EngineCore/Actor.h>

class ACombat : public AActor
{
public:
	// 持失切 社瑚切
	ACombat();
	~ACombat();

	// delete funcion

	ACombat(const ACombat& _Other) = delete;
	ACombat(ACombat&& _Other) noexcept = delete;
	ACombat& operator=(const ACombat& _Other) = delete;
	ACombat& operator=(ACombat&& _Other) noexcept = delete;


protected:

private:

};

