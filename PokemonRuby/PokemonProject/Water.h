#pragma once
#include <EngineCore/Actor.h>

class AWater : public AActor
{
public:
	// 持失切 社瑚切
	AWater();
	~AWater();

	// delete funcion

	AWater(const AWater& _Other) = delete;
	AWater(AWater&& _Other) noexcept = delete;
	AWater& operator=(const AWater& _Other) = delete;
	AWater& operator=(AWater&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetActorLocationTile(FVector2D _location);

protected:

private:
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
};

