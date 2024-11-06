#include "PreCompile.h"
#include "TileMapMode.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

ATileMapMode::ATileMapMode()
{
}

ATileMapMode::~ATileMapMode()
{
}

void ATileMapMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATileMapMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		GroundTileMap->SetTileLocation(MousePos, 2);
	}
}


