#include "precompile.h"
#include "PokemonBattleSelect.h"


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
        CurrentSubstate = ESubstate::MoveSelect;
        break;
    case ECursorName::Bag:
        CurrentSubstate = ESubstate::ItemSelect;
        break;
    case ECursorName::Pokemon:
        CurrentSubstate = ESubstate::PokemonSelect;
        break;
    case ECursorName::Run:
        CurrentSubstate = ESubstate::CantRunMessage1;
        break;
    default:
        break;
    }