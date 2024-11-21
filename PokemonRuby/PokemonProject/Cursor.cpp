#include "PreCompile.h"
#include "Cursor.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>


#include"PokemonEnum.h"

FVector2D CursorPositions[] = {
    FVector2D(740, 640), // LEFTUP
    FVector2D(1030, 640), // RIGHTUP
    FVector2D(740, 720), // LEFTDOWN
    FVector2D(1030, 720)  // RIGHTDOWN
};

ACursor::ACursor()
{
    CursorRender = CreateDefaultSubObject<USpriteRenderer>();
    CursorRender->SetOrder(ERenderOrder::FADE);
    CursorRender->SetSprite("Cursor.png");
    CursorRender->SetSpriteScale(1.0f);
    CursorRender->CreateAnimation("Cursor", "Cursor.png", 0, 0, 0.3f);
    CursorRender->ChangeAnimation("Cursor");
    CursorRender->SetComponentLocation({ 740, 640 });
    CursorRender->SetActive(false);
}


ACursor::~ACursor()
{

}


void ACursor::BeginPlay()
{
    Super::BeginPlay();
}

void ACursor::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    FVector2D CurrentLocation = CursorRender->GetComponentLocation();
    FVector2D NewLocation = CurrentLocation;

    // 이동 방향을 추적하기 위한 변수
    FVector2D Offset(0, 0);

    // 방향키 입력을 처리
    if (UEngineInput::GetInst().IsDown('W'))
    {
        Offset.Y = -1; // 위로 이동
    }
    if (UEngineInput::GetInst().IsDown('S'))
    {
        Offset.Y = 1;  // 아래로 이동
    }
    if (UEngineInput::GetInst().IsDown('A'))
    {
        Offset.X = -1; // 왼쪽으로 이동
    }
    if (UEngineInput::GetInst().IsDown('D'))
    {
        Offset.X = 1;  // 오른쪽으로 이동
    }

    // 새로운 위치 계산
    if (Offset.X != 0 || Offset.Y != 0)
    {
        FVector2D CurrentPos;
        int CurrentIndex = -1;

        // 현재 위치에 맞는 인덱스를 찾음
        for (int i = 0; i < 4; i++)
        {
            if (CursorPositions[i] == CurrentLocation)
            {
                CurrentIndex = i;
                break;
            }
        }

        if (CurrentIndex != -1)
        {
            // X, Y 방향으로 이동
            int TargetIndex = CurrentIndex;

            if (Offset.Y != 0)
            {
                // 위/아래 이동 처리
                if (Offset.Y < 0 && CurrentIndex > 1)
                {
                    TargetIndex -= 2; // 위로 이동
                }
                else if (Offset.Y > 0 && CurrentIndex < 2)
                {
                    TargetIndex += 2; // 아래로 이동
                }
            }

            if (Offset.X != 0)
            {
                // 왼쪽/오른쪽 이동 처리
                if (Offset.X < 0 && (CurrentIndex == 1 || CurrentIndex == 3))
                {
                    TargetIndex -= 1; // 왼쪽으로 이동
                }
                else if (Offset.X > 0 && (CurrentIndex == 0 || CurrentIndex == 2))
                {
                    TargetIndex += 1; // 오른쪽으로 이동
                }
            }

            // TargetIndex가 유효한 경우에만 이동
            if (TargetIndex >= 0 && TargetIndex < 4)
            {
                NewLocation = CursorPositions[TargetIndex];
            }

            // 커서 위치 업데이트
            CursorRender->SetComponentLocation(NewLocation);
        }
    }
}
