#include "PreCompile.h"
#include "PokemonMap.h"
#include <EngineCore/EngineAPICore.h>

APokemonMap::APokemonMap()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	SetActorScale(WindowSize.Half());
	SetActorLocation(WindowSize.Half());
}

APokemonMap::~APokemonMap()
{
}

