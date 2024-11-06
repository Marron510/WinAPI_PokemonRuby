#include "PreCompile.h"
#include "PokemonMapMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "PokemonMap.h"
#include "TileMap.h"
#include "Flower.h"

APokemonMapMode::APokemonMapMode()
{

}

APokemonMapMode::~APokemonMapMode()
{

}


void APokemonMapMode::BeginPlay()
{
	
	{
		APokemonMap* NewActor = GetWorld()->SpawnActor<APokemonMap>();
		
		{

			FIntPoint TileSize;
			
			GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
			GroundTileMap->Create("TileSet", {130, 82}, { 96, 96 });
			

			for (int y = 0; y < 82; y++)
			{
				for (int x = 0; x < 130; x++)
				{
					GroundTileMap->SetTileIndex({ x,y }, { 0, 0 }, { 96, 96 }, 0);
				}
			}
		}
	}
}

void APokemonMapMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	/*if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse2");
	}*/

}