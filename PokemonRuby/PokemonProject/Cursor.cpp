#include "PreCompile.h"
#include "Cursor.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>


#include"PokemonEnum.h"



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

    FVector2D Offset(0, 0);

    if (UEngineInput::GetInst().IsDown('W'))
    {
        Offset.Y = -1; 
    }
    if (UEngineInput::GetInst().IsDown('S'))
    {
        Offset.Y = 1;  
    }
    if (UEngineInput::GetInst().IsDown('A'))
    {
        Offset.X = -1; 
    }
    if (UEngineInput::GetInst().IsDown('D'))
    {
        Offset.X = 1;  
    }

    if (0 != Offset.X || 0 != Offset.Y)
    {
        FVector2D CurrentPos;
        int CurrentIndex = -1;

        for (int i = 0; i < 4; i++)
        {
            if (MenuCursorPositions[i] == CurrentLocation)
            {
                CurrentIndex = i;
                break;
            }
        }

        if (CurrentIndex != -1)
        {
            int TargetIndex = CurrentIndex;

            if (Offset.Y != 0)
            {
                if (Offset.Y < 0 && CurrentIndex > 1)
                {
                    TargetIndex -= 2;
                }
                else if (Offset.Y > 0 && CurrentIndex < 2)
                {
                    TargetIndex += 2;
                }
            }

            if (Offset.X != 0)
            {
                if (Offset.X < 0 && (CurrentIndex == 1 || CurrentIndex == 3))
                {
                    TargetIndex -= 1;
                }
                else if (Offset.X > 0 && (CurrentIndex == 0 || CurrentIndex == 2))
                {
                    TargetIndex += 1;
                }
            }

            if (TargetIndex >= 0 && TargetIndex < 4)
            {
                NewLocation = MenuCursorPositions[TargetIndex];
            }

            CursorRender->SetComponentLocation(NewLocation);
        }
    }
}

FVector2D* ACursor::GetCursorPositionsForState(ECursorState State)
{
    switch (State)
    {
    case ECursorState::Menu:
        return MenuCursorPositions;
    case ECursorState::Battle:
        return BattleCursorPositions;
    case ECursorState::SelectPokemon:
        return SelectPokemonCursorPositions;
    case ECursorState::Bag:
        return BagCursorPositions;
    default:
        return MenuCursorPositions;
    }
}


