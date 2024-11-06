#pragma once
#include <EngineCore/Actor.h>

class ASea : public AActor
{
public:
	// 持失切 社瑚切
	ASea();
	~ASea();

	// delete funcion

	ASea(const ASea& _Other) = delete;
	ASea(ASea&& _Other) noexcept = delete;
	ASea& operator=(const ASea& _Other) = delete;
	ASea& operator=(ASea&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetActorLocationTile(FVector2D _location);

protected:

private:
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
};

