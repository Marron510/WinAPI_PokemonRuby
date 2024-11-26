#include "PreCompile.h"
#include "Truck.h"

#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"
#include "Player.h"

ATruck::ATruck()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	SpriteRenderer->SetSprite("RealTruck.png");
	SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->CreateAnimation("RealTruck", "RealTruck.png", 0, 1, 0.5f);
	SpriteRenderer->ChangeAnimation("RealTruck");
	SpriteRenderer->SetOrder(ERenderOrder::TRUCK);
	SpriteRenderer->SetComponentLocation({ 82 * 96, 70 * 96 });
	SpriteRenderer->SetActive(true);
}

ATruck::~ATruck()
{

}

void ATruck::BeginPlay()
{
	Super::BeginPlay();
}

void ATruck::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


void ATruck::SetActorLocationTile(FVector2D _location)
{
	FVector2D Newloacation = _location.operator*(96);
	Newloacation.X += 48;
	Newloacation.Y += 48;
	SetActorLocation(Newloacation);
}
