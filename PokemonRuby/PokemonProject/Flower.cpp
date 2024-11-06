#include "PreCompile.h"
#include "Flower.h"
#include <EngineCore/SpriteRenderer.h>

AFlower::AFlower()
{
	SetObject({ 96,70 });
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	SpriteRenderer->SetSprite("Flower.png");
	SpriteRenderer->SetComponentScale({ 200 , 200 });
	SpriteRenderer->CreateAnimation("FlowerMove", "Flower.png", 0, 2, 0.5f);
	SpriteRenderer->ChangeAnimation("FlowerMove");
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


void AFlower::SetObject(FVector2D _location)
{
	FVector2D ObjectLocation = _location;
	ObjectLocation.operator*(96);
	int LocationX = static_cast<int>(ObjectLocation.iX());
	int LocationY = static_cast<int>(ObjectLocation.iY());
	
	SetActorLocation({ LocationX , LocationY });
}