#pragma once
#include <EngineCore/Actor.h>


class AFlower : public AActor
{
public:
	// 持失切 社瑚切
	AFlower();
	~AFlower();

	// delete funcion

	AFlower(const AFlower& _Other) = delete;
	AFlower(AFlower&& _Other) noexcept = delete;
	AFlower& operator=(const AFlower& _Other) = delete;
	AFlower& operator=(AFlower&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetObject(FVector2D _location);

protected:

private:
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
};

