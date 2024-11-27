#pragma once
#include <EngineCore/Actor.h>
#include "PokemonEnum.h"

class AMother : public AActor
{
public:
	enum class ENPCDirection
	{
		UP_Left_Arm,
		UP_Right_Arm,
		DOWN_Left_Arm,
		DOWN_Right_Arm,
		LEFT_Left_Arm,
		LEFT_Right_Arm,
		RIGHT_Left_Arm,
		RIGHT_Right_Arm,
		NONE
	};
	
	
	// 생성자 소멸자
	AMother();
	~AMother();
	

	// delete funcion

	AMother(const AMother& _Other) = delete;
	AMother(AMother&& _Other) noexcept = delete;
	AMother& operator=(const AMother& _Other) = delete;
	AMother& operator=(AMother&& _Other) noexcept = delete;

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
	FVector2D Position;                  // 위치 정보
	FVector2D TileSize = FVector2D(96, 96);
	FVector2D TargetLocation = FVector2D::ZERO; // 목표 위치
	FVector2D CurrentPosition = FVector2D::ZERO; // 현재 위치
	float MoveSpeed = 5.0f; // 이동 속도
	bool IsMoving = false; // 이동 중 여부
	float MoveTime = 0.0f; // 이동 시간
	ENPCDirection CurrentDirection = ENPCDirection::NONE; // 현재 방향
	ENPCDirection LastDirection = ENPCDirection::NONE; // 마지막으로 설정된 방향
	class UTimeEvent TimeEventer;
	bool bIsLeftArm = true; // 현재 왼팔인지 여부
};

