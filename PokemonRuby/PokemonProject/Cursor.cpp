#include "PreCompile.h"
#include "Cursor.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>


#include"PokemonEnum.h"

FVector2D CursorPositions[] = {
    FVector2D(574, 506), // LEFTUP
    FVector2D(801, 506), // RIGHTUP
    FVector2D(574, 582), // LEFTDOWN
    FVector2D(801, 582)  // RIGHTDOWN
};
std::string CursorString[static_cast<int>(ACursor::ECursorDir::MAX)] =
{
    "LEFTUP",
    "RIGHTUP",
    "LEFTDOWN",
    "RIGHTDOWN"
};

ACursor::ACursor()
{
    CursorRender = CreateDefaultSubObject<USpriteRenderer>();
    CursorRender->SetSprite("Cursor.png");
    CursorRender->SetComponentScale({ 100, 100 }); 
    CursorRender->CreateAnimation("Cursor", "Cursor.png", 0, 0, 0.3f);
    CursorRender->SetOrder(ERenderOrder::CURSOR);  

    CursorRender->SetComponentLocation({ 600, 600 });
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

    if (UEngineInput::GetInst().IsDown('W'))
    {
        NewLocation = CursorPositions[0]; 
    }
    if (UEngineInput::GetInst().IsDown('S')) 
    {
        NewLocation = CursorPositions[2]; 
    }
    if (UEngineInput::GetInst().IsDown('A'))
    {
        NewLocation = CursorPositions[0]; 
    }
    if (UEngineInput::GetInst().IsDown('D')) 
    {
        NewLocation = CursorPositions[1];
    }

    if (NewLocation != CurrentLocation)
    {
       
        float MinDistance = CursorPosMax;
        FVector2D NearestPosition;
        

        for (int i = 0; i < 4; i++)
        {
            float Distance = FVector2D::Dist(NewLocation, CursorPositions[i]);
            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                NearestPosition = CursorPositions[i];
            }
        }

        CursorRender->SetComponentLocation(NearestPosition);
    }

}