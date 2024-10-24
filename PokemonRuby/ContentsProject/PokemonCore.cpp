#include "PreCompile.h"
#include "PokemonCore.h"
#include <EngineCore/EngineAPICore.h>


PokemonCore::PokemonCore()
{

}

PokemonCore::~PokemonCore()
{

}

void PokemonCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("Play");
	UEngineAPICore::GetCore()->CreateLevel("End");
}

void PokemonCore::Tick()
{
}