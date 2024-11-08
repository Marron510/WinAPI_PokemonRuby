#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EngineCore/Level.h>
#include "TItleMap.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	{
		ATitleGameMode* NewActor = GetWorld()->SpawnActor<ATitleGameMode>();
	}
}
