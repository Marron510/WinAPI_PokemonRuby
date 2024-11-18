#include "PreCompile.h"
#include "Cursor.h"

#include <EngineBase/EngineString.h>
#include <EngineCore/SpriteRenderer.h>

#include"PokemonEnum.h"


std::string CursorString[static_cast<int>(ACursor::ECursorDir::MAX)] =
{
    "LEFTUP",
    "RIGHTUP",
    "LEFTDOWN",
    "RIGHTDOWN"
};

ACursor::ACursor()
{
    {
        CursorRender = CreateDefaultSubObject<USpriteRenderer>();
        CursorRender->SetSprite("Cursor.png");

        CursorRender->SetComponentScale({ 100, 100 });

        CursorRender->CreateAnimation("Cursor", "Cursor.png", 0, 0, 0.3f);
        CursorRender->SetOrder(ERenderOrder::CURSOR);

        CursorRender->SetComponentLocation({ 700, 700 });
    }
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
}