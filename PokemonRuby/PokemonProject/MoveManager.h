#pragma once

#include <EngineBase/EngineMath.h>
#include <unordered_map>
#include <string>

class USpriteRenderer; // 스프라이트 렌더링을 위한 클래스

class MoveManager
{
public:
    enum class ENPCDirection
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    MoveManager(FVector2D& InPosition, USpriteRenderer* InSpriteRenderer);
    ~MoveManager();

    void Move(ENPCDirection Direction, float DeltaTime); // 이동 시작
    void UpdateMovement(float DeltaTime);               // 이동 업데이트
    void StopMovement();                                // 이동 멈춤
    void SetSpeed(float Speed);                         // 이동 속도 설정
    bool IsCurrentlyMoving() const;                     // 이동 중인지 확인
    void SetDirection(ENPCDirection Direction);
private:
    FVector2D& Position;                 // 제어할 NPC의 위치 참조
    FVector2D TargetLocation;            // 목표 위치
    USpriteRenderer* SpriteRenderer;     // 애니메이션을 처리할 스프라이트 렌더러
    bool bIsMoving = false;              // 현재 이동 중인지 여부
    float WalkSpeed = 100.0f;            // 이동 속도
    float WalkTime = 0.0f;               // 이동 경과 시간

    ENPCDirection CurrentDirection;

    void UpdateAnimation(ENPCDirection Direction); // 방향에 따른 애니메이션 변경
};
