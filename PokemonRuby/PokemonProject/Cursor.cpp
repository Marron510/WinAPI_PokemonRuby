#include "PreCompile.h"
#include "Cursor.h"
#include <EngineCore/SpriteRenderer.h>

ACursor::ACursor()
{
    {
        SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

        SpriteRenderer->SetSprite("Cursor.png");

        SpriteRenderer->SetComponentScale({ 100, 100 });

        SpriteRenderer->CreateAnimation("Cursor", "Cursor.png", 0, 0, 0.1f);
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