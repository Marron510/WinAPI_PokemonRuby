#pragma once
#include <EngineCore/Actor.h>

class AMother : public AActor
{
public:
	// 持失切 社瑚切
	AMother();
	~AMother();

	// delete funcion

	AMother(const AMother& _Other) = delete;
	AMother(AMother&& _Other) noexcept = delete;
	AMother& operator=(const AMother& _Other) = delete;
	AMother& operator=(AMother&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

