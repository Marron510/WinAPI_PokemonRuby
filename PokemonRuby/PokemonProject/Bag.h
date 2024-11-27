#pragma once
#include <EngineCore/Actor.h>

class ABag : public AActor
{
public:
	// 持失切 社瑚切
	ABag();
	~ABag();

	// delete funcion

	ABag(const ABag& _Other) = delete;
	ABag(ABag&& _Other) noexcept = delete;
	ABag& operator=(const ABag& _Other) = delete;
	ABag& operator=(ABag&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetActorLocationTile(FVector2D _location);

protected:

private:
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
};

