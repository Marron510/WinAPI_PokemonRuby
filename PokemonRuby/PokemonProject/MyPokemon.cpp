#include "PreCompile.h"
#include "MyPokemon.h"


#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

AMyPokemon::AMyPokemon()
{
	Treecko = CreateDefaultSubObject<USpriteRenderer>();
	Treecko->SetOrder(ERenderOrder::POKEMON);
	Treecko->SetSprite("Treecko.png");
	FVector2D MapScale = Treecko->SetSpriteScale(1.0f);
	Treecko->CreateAnimation("Treecko", "Treecko.png", 0, 0, 0.2f);
	Treecko->SetComponentLocation({ 336, 416 });
	
	// 포켓몬은 맵으로 만들어서 관리?
	// 커서를 포켓몬이 가지는 형식으로
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