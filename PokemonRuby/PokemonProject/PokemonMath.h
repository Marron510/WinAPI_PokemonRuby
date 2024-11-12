#pragma once
#include <EngineBase/EngineMath.h>



struct FTileVector
{
public:
    const static FTileVector Zero;
    const static FTileVector Up;
    const static FTileVector Down;
    const static FTileVector Left;
    const static FTileVector Right;

    int X = 0;
    int Y = 0;

    FTileVector()
    {
    }

    FTileVector(int _X, int _Y)
        : X(_X), Y(_Y)
    {
    }

    FTileVector(const FVector2D& _Vector)
        : X(std::lround(_Vector.X) / 96), Y(std::lround(_Vector.Y) / 96)
    {
    }

    FTileVector operator-()
    {
        return FTileVector(-X, -Y);
    }

    


    FTileVector& operator=(const FTileVector& _Other)
    {
        X = _Other.X;
        Y = _Other.Y;
        return *this;
    }

    bool operator==(const FTileVector& _Other) const
    {
        return X == _Other.X && Y == _Other.Y;
    }

    bool operator!=(const FTileVector& _Other) const
    {
        return X != _Other.X || Y != _Other.Y;
    }

    FTileVector operator+(const FTileVector& _Other) const
    {
        FTileVector NewPos = *this;
        NewPos.X += _Other.X;
        NewPos.Y += _Other.Y;
        return NewPos;
    }

    FTileVector& operator+=(const FTileVector& _Other)
    {
        X += _Other.X;
        Y += _Other.Y;
        return *this;
    }

    FTileVector operator-(const FTileVector& _Other) const
    {
        return FTileVector(X - _Other.X, Y - _Other.Y);
    }

    FTileVector operator*(int _Value) const
    {
        return FTileVector(X * _Value, Y * _Value);
    }

    bool operator<(const FTileVector& _Other) const
    {
        if (X == _Other.X)
        {
            if (Y == _Other.Y)
            {
                return false;
            }

            return Y < _Other.Y;
        }

        return X < _Other.X;
    }

    bool operator>(const FTileVector& _Other) const
    {
        return (*this != _Other) && !(*this < _Other);
    }

    FVector2D ToFVector() const
    {
        return FVector2D(96 * X, 96 * Y);
    }

    std::string ToDirectionString() const
    {
        if (*this == Up)
        {
            return "Up";
        }
        else if (*this == Down)
        {
            return "Down";
        }
        else if (*this == Left)
        {
            return "Left";
        }
        else if (*this == Right)
        {
            return "Right";
        }

        return "None";
    }

    static std::vector<std::string> AllDirectionNames()
    {
        return { "Down", "Up", "Left", "Right" };
    }

    std::string ToString() const
    {
        return "[X : " + std::to_string(X) + " Y : " + std::to_string(Y) + "]";
    }

};
class UPokemonMath
{
public:
    // 持失切 社瑚切


    // delete funcion

    UPokemonMath(const UPokemonMath& _Other) = delete;
    UPokemonMath(UPokemonMath&& _Other) noexcept = delete;
    UPokemonMath& operator=(const UPokemonMath& _Other) = delete;
    UPokemonMath& operator=(UPokemonMath&& _Other) noexcept = delete;


    static float Lerp(float _Start, float _End, float _t);
    static FVector2D Lerp(const FVector2D& _Start, const FVector2D& _End, float _t);
    static FVector2D Lerp(const FTileVector& _Start, const FTileVector& _End, float _t);




protected:

private:
    
};

