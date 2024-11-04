#pragma once
#include <EngineCore/Actor.h>

class ATruckMap : public AActor
{
public:
	// 持失切 社瑚切
	ATruckMap();
	~ATruckMap();

	// delete funcion

	ATruckMap(const ATruckMap& _Other) = delete;
	ATruckMap(ATruckMap&& _Other) noexcept = delete;
	ATruckMap& operator=(const ATruckMap& _Other) = delete;
	ATruckMap& operator=(ATruckMap&& _Other) noexcept = delete;


protected:

private:

};

