#pragma once
#include "PokemonMath.h"
#include <list>

class UPokemonInput
{
public:
    // constructor destructor
    UPokemonInput();
    ~UPokemonInput();

    // delete Function
    UPokemonInput(const UPokemonInput& _Other) = delete;
    UPokemonInput(UPokemonInput&& _Other) noexcept = delete;
    UPokemonInput& operator=(const UPokemonInput& _Other) = delete;
    UPokemonInput& operator=(UPokemonInput&& _Other) noexcept = delete;

    static FTileVector GetPressDirection()
    {

        
        
        FTileVector NextDirection = FTileVector::Zero;

        if (UEngineInput::GetInst().IsPress('S'))
        {
            NextDirection = FTileVector::Down;
        }
        else if (UEngineInput::GetInst().IsPress('W'))
        {
            NextDirection = FTileVector::Up;
        }
        else if (UEngineInput::GetInst().IsPress('A'))
        {
            NextDirection = FTileVector::Left;
        }
        else if (UEngineInput::GetInst().IsPress('D'))
        {
            NextDirection = FTileVector::Right;
        }

        return NextDirection;
    }

    static FTileVector GetDownDirection()
    {
        FTileVector NextDirection = FTileVector::Zero;
        if (UEngineInput::GetInst().IsDown('S'))
        {
            NextDirection = FTileVector::Down;
        }
        else if (UEngineInput::GetInst().IsDown('W'))
        {
            NextDirection = FTileVector::Up;
        }
        else if (UEngineInput::GetInst().IsDown('A'))
        {
            NextDirection = FTileVector::Left;
        }
        else if (UEngineInput::GetInst().IsDown('D'))
        {
            NextDirection = FTileVector::Right;
        }

        return NextDirection;
    }

    static bool IsAnykeyDown()
    {
        for (int Key : AnykeyList)
        {
            if (true == UEngineInput::GetInst().IsDown(Key))
            {
                return true;
            }
        }

        for (char Ch = '0'; Ch <= '9'; ++Ch)
        {
            if (true == UEngineInput::GetInst().IsDown(Ch))
            {
                return true;
            }
        }

        for (char Ch = 'A'; Ch <= 'Z'; ++Ch)
        {
            if (true == UEngineInput::GetInst().IsDown(Ch))
            {
                return true;
            }
        }

        return false;
    }



protected:

private:
    static std::list<int> AnykeyList;
};

