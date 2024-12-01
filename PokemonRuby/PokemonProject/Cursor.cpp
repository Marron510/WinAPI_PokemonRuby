#include "PreCompile.h"
#include "Cursor.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>


#include "PokemonEnum.h"
#include "MyPokemon.h"
#include "PokemonBattleMode.h"
#include "PokemonText.h"


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
    CurrentState = ECursorState::Menu;
}


ACursor::~ACursor()
{

}


void ACursor::BeginPlay()
{
    Super::BeginPlay();
    ChatText = GetWorld()->SpawnActor<APokemonText>();
}

void ACursor::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    // 현재 상태에 따라 커서 위치 배열 가져오기
    FVector2D* CurrentPositions = GetCursorPositionsForState(CurrentState);
    FVector2D CurrentLocation = CursorRender->GetComponentLocation();
    FVector2D NewLocation = CurrentLocation;

    // 입력 처리
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

    // 커서 이동 로직
    if (Offset.X != 0 || Offset.Y != 0)
    {
        int CurrentIndex = -1;

        for (int i = 0; i < 4; i++)
        {
            if (CurrentPositions[i] == CurrentLocation)
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
                NewLocation = CurrentPositions[TargetIndex];
            }

            CursorRender->SetComponentLocation(NewLocation);
        }
    }

    // 상태에 따른 처리
    if (CurrentState == ECursorState::Menu)
    {
        HandleMenuInput();
    }
    else if (CurrentState == ECursorState::Battle)
    {
        HandleBattleInput();

        // 커서 위치에 따른 PP 텍스트 렌더링
        UpdatePPTextRendering(CurrentLocation);
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
    case ECursorState::ABag:
        return BagCursorPositions;
    default:
        return MenuCursorPositions;
    }
}


void ACursor::SetState(ECursorState NewState)
{
    CurrentState = NewState;

    switch (NewState)
    {
    case ECursorState::Menu:
        break;
    case ECursorState::Battle:
        bPPTextEnabled = true; 
        IsFirstBattleZPressIgnored = true;
        break;
    default:
        break;
    }

    FVector2D* StartPositions = GetCursorPositionsForState(CurrentState);
    CursorRender->SetComponentLocation(StartPositions[0]);
}


void ACursor::SetBattleModeInstance(class APokemonBattleMode* BattleMode)
{
    BattleModeInstance = BattleMode;  
}

void ACursor::HandleMenuInput()
{
    if (UEngineInput::GetInst().IsDown('Z') && IsFirstMenuZPressIgnored)
    {
        IsFirstMenuZPressIgnored = false;
        return;
    }

    if (UEngineInput::GetInst().IsDown('Z') && !IsFirstMenuZPressIgnored)
    {
        if (BattleModeInstance != nullptr)
        {
            BGMPlayer = UEngineSound::Play("SEClick.mp3");
            BattleModeInstance->HandleMenuSelection(CursorRender->GetComponentLocation());
        }
    }
}

void ACursor::HandleBattleInput()
{
    if (UEngineInput::GetInst().IsPress('Z') && IsFirstBattleZPressIgnored)
    {
        IsFirstBattleZPressIgnored = false;
        return;
    }

    if (UEngineInput::GetInst().IsDown('Z') && !IsFirstBattleZPressIgnored)
    {
        if (BattleModeInstance != nullptr)
        {
            BGMPlayer = UEngineSound::Play("SEClick.mp3");

            BattleModeInstance->SkillTextOff();

            bPPTextEnabled = false; 

            BattleModeInstance->GetMyPokemonSkill1PP()->SetOrder(ERenderOrder::WATER);
            BattleModeInstance->GetMyPokemonSkill2PP()->SetOrder(ERenderOrder::WATER);

            BattleModeInstance->HandleSkillSelection(CursorRender->GetComponentLocation());
        }
    }
}


void ACursor::UpdatePPTextRendering(const FVector2D& CursorLocation)
{
    if (!bPPTextEnabled)
    {
        BattleModeInstance->GetMyPokemonSkill1PP()->SetOrder(ERenderOrder::WATER);
        BattleModeInstance->GetMyPokemonSkill2PP()->SetOrder(ERenderOrder::WATER);
        return;
    }

    if (CursorLocation == BattleCursorPositions[0])
    {
        BattleModeInstance->GetMyPokemonSkill1PP()->SetOrder(ERenderOrder::FONT);
        BattleModeInstance->GetMyPokemonSkill2PP()->SetOrder(ERenderOrder::WATER);
    }
    else if (CursorLocation == BattleCursorPositions[1])
    {
        BattleModeInstance->GetMyPokemonSkill1PP()->SetOrder(ERenderOrder::WATER);
        BattleModeInstance->GetMyPokemonSkill2PP()->SetOrder(ERenderOrder::FONT);
    }
    else
    {
        BattleModeInstance->GetMyPokemonSkill1PP()->SetOrder(ERenderOrder::WATER);
        BattleModeInstance->GetMyPokemonSkill2PP()->SetOrder(ERenderOrder::WATER);
    }
}