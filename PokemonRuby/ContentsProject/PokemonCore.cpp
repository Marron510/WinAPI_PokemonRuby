#include "PreCompile.h"
#include "PokemonCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
#include "Player.h"

PokemonCore::PokemonCore()
{

}

PokemonCore::~PokemonCore()
{

}

void PokemonCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Title"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Tutorial"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Littleroot town"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Player house"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Professor Birch's house"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Labor  Professor Birch"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Oldale Town"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Pokemon Center"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Oldale Town Pokemon Center"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Oldale Town Pokemon Supermarket"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Oldale house 1"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Oldale house 2"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Route 101"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Route 102"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Route 103"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Petalburg City"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Petalburg City Pokemon Center"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Petalburg City Pokemon Supermarket"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Petalburg house 1"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Petalburg house 2"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Petalburg Gym"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Battle"); UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("PokemonUI");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("PlayerBag");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Ending");
	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void PokemonCore::Tick()
{
}