#include "PreCompile.h"
#include "PokemonCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include "PokemonGameMode.h"
#include "Player.h"

PokemonCore::PokemonCore()
{

}

PokemonCore::~PokemonCore()
{

}

void PokemonCore::BeginPlay()
{

	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("PokemonResources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		//UEngineDebug::OutPutString(FilePath);
	}



	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Pokemon_Ruby");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Title"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	/*UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Tutorial"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Littleroot town"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Player house"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Professor Birch's house"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Labor  Professor Birch"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Oldale Town"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Pokemon Center"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Oldale Town Pokemon Center"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Oldale Town Pokemon Supermarket"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Oldale house 1"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Oldale house 2"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Route 101"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Route 102"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Route 103"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Petalburg City"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Petalburg City Pokemon Center"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Petalburg City Pokemon Supermarket"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Petalburg house 1"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Petalburg house 2"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Petalburg Gym"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Battle"); UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("PokemonUI");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("PlayerBag");
	UEngineAPICore::GetCore()->CreateLevel<APokemonGameMode, APlayer>("Ending");*/
	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void PokemonCore::Tick()
{
}