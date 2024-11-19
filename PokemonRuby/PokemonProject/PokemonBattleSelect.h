#pragma once
#include <EngineCore/Actor.h>
#include "Cursor.h"

class PokemonBattleSelect : public AActor
{
private:
    enum ECursorName
    {
        Fight,
        Bag,
        Pokemon,
        Run
    };

    enum class ESubstate
    {
        None,
        SkillSelect,
        MoveSelect,
        PokemonSelect,
        ItemSelect,
        CantRunMessage1,
        CantRunMessage2,
        End
    };

    int CurrentSelectionRow = 0;  
    int CurrentSelectionCol = 0;  
    int MaxRows = 2;  
    int MaxCols = 2; 

    ESubstate CurrentSubstate = ESubstate::None;

    std::vector<std::vector<ECursorName>> MenuOptions = {
        { ECursorName::Fight, ECursorName::Bag },
        { ECursorName::Pokemon, ECursorName::Run }
    };

public:
    PokemonBattleSelect();
    ~PokemonBattleSelect();

    void UpdateCursorPosition(float DeltaTime);
    void SelectOption();
    void HandleInput();  

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};
