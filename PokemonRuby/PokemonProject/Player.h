#pragma once
#include <EngineCore/Actor.h>

class APlayer : public AActor
{
public:
	enum class APlayerState
	{
		NONE,
		IDLE,
		WALK,
		RUN,
		JUMP,
	};

	enum class APlayerDir
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};


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
	void PlayerCameraCheck();
	void PlayerDebugCheck(float _DeltaTime);

	void LevelChangeStart();
	void LevelChangeEnd();
	void SetObject(FVector2D _location);
	void SetActorLocationTile(FVector2D _location);






	void StateUpdate(float _DeltaTime);

	void ChangeAnimation(APlayerState _State);
	void StateChange(APlayerState _State, bool _Restart = false);


	FVector2D Lerp(const FVector2D& _Start, const FVector2D& _End, float _t);
	FVector2D TileLerp(FVector2D _Start, FVector2D _End, float _t);

protected:

private:
	float WalkSpeed = 3.0f;
	float WalkTime = 1.0f / WalkSpeed;
	float CurWalkTime = WalkTime;


	float WalkInputLatency = 0.75f;


	FVector2D Direction;
	FVector2D CurPos;
	FVector2D NextPos;


	int MySpriteIndex = 0;
	FVector2D MapSize = FVector2D::ZERO;
	
	APlayerState CurPlayerState = APlayerState::Idle;
	APlayerDir  DirType;


	class USpriteRenderer* SpriteRenderer;
	class USpriteRenderer* SpriteMapRenderer;
	
};

