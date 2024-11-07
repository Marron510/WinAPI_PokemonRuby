#pragma once
#include <EngineCore/Actor.h>

class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelChangeStart();
	void LevelChangeEnd();
	void SetObject(FVector2D _location);
	void SetActorLocationTile(FVector2D _location);

protected:

private:
	float Speed = 200.0f;
	int MySpriteIndex = 0;
	FVector2D MapSize = FVector2D::ZERO;
	
	class USpriteRenderer* SpriteRenderer;
	class USpriteRenderer* SpriteMapRenderer;
	
};

