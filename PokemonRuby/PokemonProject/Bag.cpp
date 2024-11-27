#include "PreCompile.h"
#include "Bag.h"

#include <EngineCore/SpriteRenderer.h>
#include "PokemonEnum.h"

ABag::ABag()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	SpriteRenderer->SetSprite("Bag.png");
	SpriteRenderer->SetComponentScale({ 80 , 80 });
	SpriteRenderer->CreateAnimation("Bag", "Bag.png", 0, 0, 0.5f);
	SpriteRenderer->ChangeAnimation("Bag");
	SpriteRenderer->SetOrder(ERenderOrder::FLOWER);
}

ABag::~ABag()
{

}



void ABag::BeginPlay()
{
	Super::BeginPlay();

}

void ABag::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ABag::SetActorLocationTile(FVector2D _location)
{
	FVector2D Newloacation = _location.operator*(96);
	Newloacation.X += 48;
	Newloacation.Y += 48;
	SetActorLocation(Newloacation);
}
