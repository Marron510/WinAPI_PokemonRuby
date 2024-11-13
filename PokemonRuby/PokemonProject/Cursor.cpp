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
        SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
        SpriteRenderer->SetSprite("Cursor.png");

        SpriteRenderer->SetComponentScale({ 100, 100 });

        SpriteRenderer->CreateAnimation("Cursor", "Cursor.png", 0, 0, 0.3f);
        SpriteRenderer->SetOrder(ERenderOrder::CURSOR);

        SpriteRenderer->SetComponentLocation({ 700, 700 });
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