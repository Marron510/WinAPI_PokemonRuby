#include "PreCompile.h"
#include "Flower.h"
#include <EngineCore/SpriteRenderer.h>
#include "PokemonEnum.h"


AFlower::AFlower()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	SpriteRenderer->SetSprite("Flower.png");
	SpriteRenderer->SetComponentScale({ 100 , 100 });
	SpriteRenderer->CreateAnimation("FlowerMove", "Flower.png", 0, 3, 0.5f);
	SpriteRenderer->ChangeAnimation("FlowerMove");
	SpriteRenderer->SetOrder(ERenderOrder::FLOWER);
}

AFlower::~AFlower()
{

}

void AFlower::BeginPlay()
{
	Super::BeginPlay();

}

void AFlower::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}


void AFlower::SetActorLocationTile(FVector2D _location)
{
	FVector2D Newloacation = _location.operator*(96);
	Newloacation.X += 48;
	Newloacation.Y += 48;
	SetActorLocation(Newloacation);
}
