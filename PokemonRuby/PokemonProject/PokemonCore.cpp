#include "PreCompile.h"
#include "PokemonCore.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "PlayerHouse1Mode.h"
#include "PlayerHouse1FloorMode.h"
#include "PlayerHouse2Mode.h"
#include "PlayerHouse2FloorMode.h"
#include "LittleRootTownMode.h"
#include "LaborProfessorBirchMode.h"

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
		UImageManager::GetInst().Load(FilePath);
	}

	{
		UImageManager::GetInst().CuttingSprite("Player_Walk_Up.png", { 64, 64 });
		UImageManager::GetInst().CuttingSprite("Player_Walk_Down.png", { 64, 64 });
		UImageManager::GetInst().CuttingSprite("Player_Walk_Right.png", { 64, 64 });
		UImageManager::GetInst().CuttingSprite("Player_Walk_Left.png", { 64, 64 });
	}

	/*{
		UImageManager::GetInst().CuttingSprite("Player_Run_Up.png", { 64, 64 });
		UImageManager::GetInst().CuttingSprite("Player_Run_Down.png", { 64, 64 });
		UImageManager::GetInst().CuttingSprite("Player_Run_Right.png", { 64, 64 });
		UImageManager::GetInst().CuttingSprite("Player_Run_Left.png", { 64, 64 });
	}*/

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Pokemon_Ruby");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1200, 800 });

	
	{
		UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse1Mode, APlayer>("PlayerHouse1");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse1FloorMode, APlayer>("PlayerHouse1Floor");
		UEngineAPICore::GetCore()->CreateLevel<ALittleRootTownMode, APlayer>("LittleRootTown");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse2Mode, APlayer>("PlayerHouse2");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse2FloorMode, APlayer>("PlayerHouse2Floor");
		UEngineAPICore::GetCore()->CreateLevel<ALaborProfessorBirchMode, APlayer>("LaborProfessorBirch");
	}



	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void PokemonCore::Tick()
{
}