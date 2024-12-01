#include "PreCompile.h"
#include "PokemonCore.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EnginePlatform/EngineSound.h>
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
#include "SelectPokemonMode.h"

#include "MyPokemon.h"
#include "Player.h"




PokemonCore::PokemonCore()
{

}

PokemonCore::~PokemonCore()
{

}

void PokemonCore::BeginPlay()
{


	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("PokemonResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UImageManager::GetInst().Load(FilePath);
		}
	}
	
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("PokemonResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Sound");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image//Intro");
		Dir.Append("Intro_0");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image//Intro");
		Dir.Append("Intro_1");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image//Intro");
		Dir.Append("Intro_2");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image//Intro");
		Dir.Append("Intro_3");

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
		Dir.Append("Player//Battle");

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
		Dir.Append("PlayMap//ThrowedBall");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("PokemonResources//Image");
		Dir.Append("TileMap//Object");

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
		UImageManager::GetInst().CuttingSprite("Player_Throw_MonsterBall.png", { 400, 288 });
	}

	

	{
		UImageManager::GetInst().CuttingSprite("Flower.png", { 168, 168 });
		UImageManager::GetInst().CuttingSprite("Sea.png", { 96, 96 });
		UImageManager::GetInst().CuttingSprite("Water.png", { 96, 96 });
		UImageManager::GetInst().CuttingSprite("Bag.png", { 96, 96 });
		UImageManager::GetInst().CuttingSprite("SelectBall.png", { 83, 72 });
		UImageManager::GetInst().CuttingSprite("SelectCursor.png", { 74, 99 });
		UImageManager::GetInst().CuttingSprite("SelectTreecko.png", { 258, 78 });
		UImageManager::GetInst().CuttingSprite("SelectTorchic.png", { 186, 78 });
		UImageManager::GetInst().CuttingSprite("SelectMudkip.png", { 230, 78 });
		UImageManager::GetInst().CuttingSprite("Monster.png", { 60, 54 });
	}

	{
		UImageManager::GetInst().CuttingSprite("RealTruck.png", { 288, 245 });
		UImageManager::GetInst().CuttingSprite("Mother.png", { 55, 67});
		UImageManager::GetInst().CuttingSprite("Child.png", { 55, 60 });
		UImageManager::GetInst().CuttingSprite("Professor.png", { 48, 60 });
	}

	{
		UImageManager::GetInst().CuttingSprite("Cursor.png", { 288, 288 });
		UImageManager::GetInst().CuttingSprite("TextWhite.png", { 20, 36 });
		UImageManager::GetInst().CuttingSprite("TextBlack.png", { 14, 24 });
		UImageManager::GetInst().CuttingSprite("ThrowBall.png", { 165, 272 });
		UImageManager::GetInst().CuttingSprite("EnemyHpBar.png", { 1, 15 });
	}

	{
		UImageManager::GetInst().CuttingSprite("Treecko.png", { 288, 288 });
		UImageManager::GetInst().CuttingSprite("Torchic.png", { 288, 288 });
		UImageManager::GetInst().CuttingSprite("Mudkip.png", { 288, 288 });
		UImageManager::GetInst().CuttingSprite("Zigzagoon.png", { 288, 288 });
		UImageManager::GetInst().CuttingSprite("Poochyena.png", { 288, 288 });
		UImageManager::GetInst().CuttingSprite("Wurmple.png", { 288, 288 });
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
		UEngineAPICore::GetCore()->CreateLevel<ASelectPokemonMode, AActor>("PokemonSelect");
		UEngineAPICore::GetCore()->CreateLevel<APokemonBattleMode, AActor>("PokemonBattle");
	}


	
		UEngineAPICore::GetCore()->OpenLevel("Title");
	
}

void PokemonCore::Tick()
{
}