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
	/*UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("Tutorial");
	UEngineAPICore::GetCore()->CreateLevel("PlayDefault");
	UEngineAPICore::GetCore()->CreateLevel("PlayerBag");
	UEngineAPICore::GetCore()->CreateLevel("PlayerMap");
	UEngineAPICore::GetCore()->CreateLevel("PokemonBag");
	UEngineAPICore::GetCore()->CreateLevel("PokemonUI");
	UEngineAPICore::GetCore()->CreateLevel("Battle");*/
	//UEngineAPICore::GetCore()->CreateLevel("PokemonDic");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void PokemonCore::Tick()
{
}