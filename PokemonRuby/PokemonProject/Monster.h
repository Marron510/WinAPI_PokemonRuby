#pragma once
#include <EngineCore/Actor.h>
#include "PokemonEnum.h"

class AMonster : public AActor
{
public:
	enum class ENPCDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};
	
	// 생성자 소멸자
	AMonster();
	~AMonster();

	// delete funcion

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetAnimationByDirection(ENPCDirection Direction);
	void SetTargetLocation(const FVector2D& Offset);
	void SetLookDirection(ENPCDirection Direction);

	class USpriteRenderer* GetRender()
	{
		return SpriteRenderer;
	}

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Position;
	FVector2D TileSize = FVector2D(96, 96);
	FVector2D TargetLocation = FVector2D::ZERO;
	FVector2D CurrentPosition = FVector2D::ZERO;
	float MoveSpeed = 5.0f; // 이동 속도
	bool IsMoving = false; // 이동 중 여부
	float MoveTime = 0.0f; // 이동 시간
	ENPCDirection CurrentDirection = ENPCDirection::NONE;
	ENPCDirection LastDirection = ENPCDirection::NONE;
	class UTimeEvent TimeEventer;
};

