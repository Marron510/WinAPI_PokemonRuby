#include "PreCompile.h"
#include "PokemonCore.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "TruckMode.h"
#include "PlayerHouse1Mode.h"
#include "PlayerHouse1FloorMode.h"
#include "PlayerHouse2Mode.h"
#include "PlayerHouse2FloorMode.h"
#include "PokemonMapMode.h"
#include "LaborProfessorBirchMode.h"
#include "TileMapMode.h"
#include "PokemonBattleMode.h"
#include "Cursor.h"

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
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("Intro//Intro_0");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}


	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("Player//Move");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("PlayMap//Exterior");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("PlayMap//Interior");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}
	
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("PlayMap//UI");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("TileMap//TileSet");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("TileMap//Flower");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("TileMap//Water");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}


	{
		UImageManager::GetInst().CuttingSprite("Player_Walk_Up.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Player_Walk_Down.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Player_Walk_Right.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Player_Walk_Left.png", { 48, 48 });
	}

	

	{
		UImageManager::GetInst().CuttingSprite("Flower.png", { 168, 168  });
		UImageManager::GetInst().CuttingSprite("Sea.png", { 96, 96 });
		UImageManager::GetInst().CuttingSprite("Water.png", { 96, 96 });
	}

	{
		UImageManager::GetInst().CuttingSprite("Cursor.png", { 96, 96 });
	}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Pokemon_Ruby");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1200, 800 });

	
	{
		UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
		UEngineAPICore::GetCore()->CreateLevel<ATruckMode, APlayer>("Truck");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse1Mode, APlayer>("PlayerHouse1");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse1FloorMode, APlayer>("PlayerHouse1Floor");
		UEngineAPICore::GetCore()->CreateLevel<APokemonMapMode, APlayer>("PokemonMap");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse2Mode, APlayer>("PlayerHouse2");
		UEngineAPICore::GetCore()->CreateLevel<APlayerHouse2FloorMode, APlayer>("PlayerHouse2Floor");
		UEngineAPICore::GetCore()->CreateLevel<ALaborProfessorBirchMode, APlayer>("LaborProfessorBirch");
		UEngineAPICore::GetCore()->CreateLevel<APokemonBattleMode, ACursor>("PokemonBattleMap");
		
	}


	
		UEngineAPICore::GetCore()->OpenLevel("Truck");
	
}

void PokemonCore::Tick()
{
}