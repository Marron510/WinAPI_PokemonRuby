#include "PreCompile.h"
#include "MyPokemon.h"


#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

AMyPokemon::AMyPokemon()
{
	MyPokemon = CreateDefaultSubObject<USpriteRenderer>();
	MyPokemon->SetOrder(ERenderOrder::POKEMON);
	MyPokemon->SetSprite("Treecko.png");
	FVector2D Scale = MyPokemon->SetSpriteScale(1.0f);
	MyPokemon->CreateAnimation("Treecko", "Treecko.png", 0, 0, 0.2f);
}


AMyPokemon::~AMyPokemon()
{

}


void AMyPokemon::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPokemon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


