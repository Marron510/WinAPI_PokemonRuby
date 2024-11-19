#include "precompile.h"
#include "PokemonBattleSelect.h"


#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "Cursor.h"


PokemonBattleSelect::PokemonBattleSelect()
{
}

PokemonBattleSelect::~PokemonBattleSelect()
{
}

void PokemonBattleSelect::BeginPlay()
{
    Super::BeginPlay();

}

void PokemonBattleSelect::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleInput();

    UpdateCursorPosition(DeltaTime);
}

void PokemonBattleSelect::HandleInput()
{
    if (UEngineInput::GetInst().IsDown('W'))  
    {
        CurrentSelectionRow = (CurrentSelectionRow - 1 + MaxRows) % MaxRows;
    }
    else if (UEngineInput::GetInst().IsDown('S'))  
    {
        CurrentSelectionRow = (CurrentSelectionRow + 1) % MaxRows;
    }
    else if (UEngineInput::GetInst().IsDown('A'))  
    {
        CurrentSelectionCol = (CurrentSelectionCol - 1 + MaxCols) % MaxCols;
    }
    else if (UEngineInput::GetInst().IsDown('D'))  
    {
        CurrentSelectionCol = (CurrentSelectionCol + 1) % MaxCols;
    }
    else if (UEngineInput::GetInst().IsDown('Z'))  
    {
        SelectOption();
    }
}

void PokemonBattleSelect::UpdateCursorPosition(float DeltaTime)
{
    FVector2D CursorPosition = FVector2D::ZERO;

    CursorPosition.X = 100.0f * CurrentSelectionCol;  
    CursorPosition.Y = 50.0f * CurrentSelectionRow;   

}

void PokemonBattleSelect::SelectOption()
{
    ECursorName selectedOption = MenuOptions[CurrentSelectionRow][CurrentSelectionCol];

    switch (selectedOption)
    {
    case ECursorName::Fight:
        CurrentSubstate = ESubstate::SkillSelect;
        break;
    case ECursorName::Bag:
        CurrentSubstate = ESubstate::ItemSelect;
        break;
    case ECursorName::Pokemon:
        CurrentSubstate = ESubstate::PokemonSelect;
        break;
    case ECursorName::Run:
        CurrentSubstate = ESubstate::MoveSelect;
        break;
    default:
        break;
    }
}
