#include "PreCompile.h"
#include "Sea.h"
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

ASea::ASea()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	SpriteRenderer->SetSprite("Sea.png");
	SpriteRenderer->SetComponentScale({ 100 , 100 });
	SpriteRenderer->CreateAnimation("SeaMove", "Sea.png", 0, 7, 0.2f);
	SpriteRenderer->ChangeAnimation("SeaMove");
	SpriteRenderer->SetOrder(ERenderOrder::WATER);
}

ASea::~ASea()
{

}

void ASea::BeginPlay()
{
	Super::BeginPlay();

}

void ASea::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}


void ASea::SetActorLocationTile(FVector2D _location)
{
	FVector2D Newloacation = _location.operator*(96);
	Newloacation.X += 48;
	Newloacation.Y += 48;
	SetActorLocation(Newloacation);
}
