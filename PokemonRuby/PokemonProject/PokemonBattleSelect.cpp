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

void PokemonBattleSelect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
    UpdateCursorPosition(_DeltaTime);


}

void PokemonBattleSelect::HandleInput()
{
}

void PokemonBattleSelect::UpdateCursorPosition(float DeltaTime)
{
    FVector2D CursorPosition = FVector2D::ZERO;  

    CursorPosition.Y = 50.0f * CurrentSelectionIndex;

}

void PokemonBattleSelect::SelectOption()
{
    ECursorName selectedOption = MenuOptions[CurrentSelectionIndex];

    switch (selectedOption)
    {
    case ECursorName::Fight:
        CurrentSubstate = ESubstate::Select;

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

void PokemonBattleSelect::HandleInput()
{
        if (UEngineInput::GetInst().IsDown('W'))
        {
            CurrentSelectionIndex = (CurrentSelectionIndex - 1 + MenuOptions.size()) % MenuOptions.size();
        }
        else if (UEngineInput::GetInst().IsDown('S'))
        {
            CurrentSelectionIndex = (CurrentSelectionIndex + 1) % MenuOptions.size();
        }
        else if (UEngineInput::GetInst().IsDown('Z'))
        {
            SelectOption();
        }
}