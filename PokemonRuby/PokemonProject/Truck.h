#pragma once
#include <EngineCore/Actor.h>


class ATruck : public AActor
{
public:
	// 持失切 社瑚切
	ATruck();
	~ATruck();

	// delete funcion

	ATruck(const ATruck& _Other) = delete;
	ATruck(ATruck&& _Other) noexcept = delete;
	ATruck& operator=(const ATruck& _Other) = delete;
	ATruck& operator=(ATruck&& _Other) noexcept = delete;
	
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetActorLocationTile(FVector2D _location);

	USpriteRenderer* GetRender()
	{
		return SpriteRenderer;
	}

protected:

private:
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
};

