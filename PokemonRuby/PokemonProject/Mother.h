#pragma once
#include <EngineCore/Actor.h>
#include "PokemonEnum.h"

class AMother : public AActor
{
public:
	// 생성자 소멸자
	AMother();
	~AMother();
	enum class ENPCDirection
	{
		UP,      // 위로 이동
		DOWN,    // 아래로 이동
		LEFT,    // 왼쪽으로 이동
		RIGHT,   // 오른쪽으로 이동
		NONE     // 움직임 없음 (Idle 상태)
	};
	// delete funcion

	AMother(const AMother& _Other) = delete;
	AMother(AMother&& _Other) noexcept = delete;
	AMother& operator=(const AMother& _Other) = delete;
	AMother& operator=(AMother&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetAnimationByDirection(ENPCDirection Direction);
	void SetTargetLocation(const FVector2D& Offset);
protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Position;                  // 위치 정보
	FVector2D TileSize = FVector2D(96, 96);
	FVector2D TargetLocation = FVector2D::ZERO; // 목표 위치
	FVector2D CurrentPosition = FVector2D::ZERO; // 현재 위치
	float MoveSpeed = 5.0f; // 이동 속도
	bool IsMoving = false; // 이동 중 여부
	float MoveTime = 0.0f; // 이동 시간
	ENPCDirection CurrentDirection = ENPCDirection::NONE; // 현재 방향
	class UTimeEvent TimeEventer;
};

