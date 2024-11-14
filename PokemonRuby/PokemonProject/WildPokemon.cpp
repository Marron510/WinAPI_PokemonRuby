#include "PreCompile.h"
#include "WildPokemon.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>



#include "PokemonEnum.h"

AWildPokemon::AWildPokemon()
{
	WildPokemon = CreateDefaultSubObject<USpriteRenderer>();
	WildPokemon->SetOrder(ERenderOrder::POKEMON);
	WildPokemon->SetSprite("Zigzagoon.png");
	FVector2D Scale = WildPokemon->SetSpriteScale(1.0f);
	WildPokemon->CreateAnimation("Zigzagoon", "Zigzagoon.png", 0, 0, 0.2f);
	
}

AWildPokemon::~AWildPokemon()
{

}




void AWildPokemon::BeginPlay()
{
	Super::BeginPlay();
}

void AWildPokemon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}