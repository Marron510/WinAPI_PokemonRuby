#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineSprite.h>

#include "PokemonMath.h"

class UEventManager;
class UEventProcessor;
class PokemonDebug;

enum class ETargetMoveState
{
    Idle,
    Walk
};

class UEventTargetSetting
{
    friend UEventManager;
public:
    UEventTargetSetting()
    {
    }

    void SetName(std::string_view _Name)
    {
        Name = UEngineString::ToUpper(_Name);
    }

    void SetPoint(const FTileVector& _Point)
    {
        Point = _Point;
    }

    void SetDirection(const FTileVector& _Direction)
    {
        Direction = _Direction;
    }

    void SetCollidable(bool _Value)
    {
        Collidable = _Value;
    }

    void SetRotatable(bool _Value)
    {
        Rotatable = _Value;
    }

    void SetWalkable(bool _Value)
    {
        Walkable = _Value;
    }

    void SetImageNameAuto()
    {
        if (true == Rotatable)
        {
            ImageName = Name + UEngineString::ToUpper("Idle.png");
        }
        else
        {
            ImageName = Name + UEngineString::ToUpper(".png");
        }
    }

    void SetImageName(std::string_view _ImageName = "")
    {
        ImageName = UEngineString::ToUpper(_ImageName);
    }

    void SetAnimNamePrefix(std::string_view _Prefix)
    {
        AnimNamePrefix = UEngineString::ToUpper(_Prefix);
    }

    void SetHeight(int _Height)
    {
        Height = _Height;
    }

private:
    std::string Name = "";
    FTileVector Point = FTileVector::Zero;
    FTileVector Direction = FTileVector::Zero;
    bool Collidable = false;
    bool Rotatable = false;
    bool Walkable = false;
    std::string ImageName = "";
    std::string AnimNamePrefix = "";
    int Height = 2;
};



class AEventTarget : public AActor
{
    friend UEventProcessor;
    friend UEventManager;
    friend PokemonDebug;
public:
    // constructor destructor
    AEventTarget();
    ~AEventTarget();

    // delete Function
    AEventTarget(const AEventTarget& _Other) = delete;
    AEventTarget(AEventTarget&& _Other) noexcept = delete;
    AEventTarget& operator=(const AEventTarget& _Other) = delete;
    AEventTarget& operator=(AEventTarget&& _Other) noexcept = delete;


    int GetHeight() const
    {
        return Height;
    }

    FTileVector GetPoint() const
    {
        return Point;
    }

    FTileVector GetDirection() const
    {
        return Direction;
    }

    void SetDirection(const FTileVector& _Direction)
    {
        Direction = _Direction;
    }

    void SetMoveState(ETargetMoveState _MoveState)
    {
        MoveState = _MoveState;
    }

    ETargetMoveState GetMoveState() const
    {
        return MoveState;
    }




protected:
    FTileVector Point = FTileVector::Zero;
    FTileVector Direction = FTileVector::Down;
    bool Collidable = false;
    bool Rotatable = false;
    bool Walkable = false;
    bool HasImage = false;
    int Height = 2;

    ETargetMoveState MoveState = ETargetMoveState::Idle;
    float MoveTime = 0.0f;
    float Timer = 0.0f;
    int MoveIndex = -1;
    bool IsExecutingMovingLogic = false;



    std::string ImageName = "";
    std::string AnimNamePrefix = "";

private:
};

