#include "PreCompile.h"
#include "Water.h"
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"


AWater::AWater()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	SpriteRenderer->SetSprite("Water.png");
	SpriteRenderer->SetComponentScale({ 100 , 100 });
	SpriteRenderer->CreateAnimation("WaterMove", "Water.png", 0, 7, 0.3f);
	SpriteRenderer->ChangeAnimation("WaterMove");
	SpriteRenderer->SetOrder(ERenderOrder::WATER);
}

AWater::~AWater()
{

}

void AWater::BeginPlay()
{
	Super::BeginPlay();

}

void AWater::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}


void AWater::SetActorLocationTile(FVector2D _location)
{
	FVector2D Newloacation = _location.operator*(96);
	Newloacation.X += 48;
	Newloacation.Y += 48;
	SetActorLocation(Newloacation);
}
