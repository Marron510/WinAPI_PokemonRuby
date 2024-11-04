
#include "PreCompile.h"
#include "TruckMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "TruckMap.h"

ATruckMode::ATruckMode()
{

}

ATruckMode::~ATruckMode()
{

}


void ATruckMode::BeginPlay()
{
	{
		ATruckMap* NewActor = GetWorld()->SpawnActor<ATruckMap>();
	}
}

void ATruckMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("PlayerHouse1");
	}

}