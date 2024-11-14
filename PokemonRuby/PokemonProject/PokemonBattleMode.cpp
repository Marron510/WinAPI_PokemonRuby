#include "PreCompile.h"
#include "PokemonBattleMode.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonMath.h"
#include "PokemonBattleMap.h"
#include "MyPokemon.h"
#include "WildPokemon.h"



APokemonBattleMode::APokemonBattleMode()
{

}

APokemonBattleMode::~APokemonBattleMode()
{

}

void APokemonBattleMode::BeginPlay()
{
	Super::BeginPlay();

	{
		APokemonBattleMap* BackImage = GetWorld()->SpawnActor<APokemonBattleMap>();
		Map = BackImage->GetCurMap();
		
		PlayerPokemonShadow = BackImage->GetPlayerPKMShadow ();
		
		EnemyPokemonShadow = BackImage->GetEnemyPokemonShadow();
		
		PlayerPokemonUI = BackImage->GetPokemonUI();
		
		EnemyPokemonUI = BackImage->GetEnemyPokemonUI();
		
	}

	{
		MyPokemon = GetWorld()->SpawnActor<AMyPokemon>();
		MyPokemon->SetActorLocation({ 1524 ,416 }); 
	}

	{
		EnemyPokemon = GetWorld()->SpawnActor<AWildPokemon>();
		EnemyPokemon->SetActorLocation({ -132 , 260 });
	}

	
}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PokemonSetting();

	BattleGroundSetting();

	
	
}

//FVector2D PokemonLocation = MyPokemon->GetActorLocation();
//FVector2D PokemonEndLocation = FVector2D({ 336 ,416 });
//if (PokemonLocation == PokemonEndLocation)
//{
//	EnemyPokemonUISetting();
//}

void APokemonBattleMode::PokemonSetting()
{
	{
		FVector2D TargetLocation = FVector2D({ 336 ,416 }); 
		FVector2D Curloc = MyPokemon->GetActorLocation();
		Curloc += FVector2D::LEFT.Half();

		if (TargetLocation == Curloc)
		{
			MyPokemon->GetActorLocation() = TargetLocation;
			EnemyPokemonUISetting();
			return;
		}

		MyPokemon->SetActorLocation(Curloc);
	}

	{
		FVector2D TargetLocation = FVector2D({ 1068 , 260 }); 
		FVector2D Curloc = EnemyPokemon->GetActorLocation();
		Curloc += FVector2D::RIGHT.Half();

		if (TargetLocation == Curloc)
		{
			EnemyPokemon->GetActorLocation() = TargetLocation;
			return;
		}

		EnemyPokemon->SetActorLocation(Curloc);
	}
}

void APokemonBattleMode::BattleGroundSetting()
{
	{
		FVector2D TargetLocation = FVector2D({ 336 , 520 }); // PlayerPokemonShadow의 최종 목적지
		FVector2D Curloc = PlayerPokemonShadow->GetComponentLocation();
		Curloc += FVector2D::LEFT.Half();
		if (TargetLocation == Curloc)
		{
			PlayerPokemonShadow->GetComponentLocation() = TargetLocation;
			return;
		}

		PlayerPokemonShadow->SetComponentLocation(Curloc);
	}

	{
		FVector2D TargetLocation = FVector2D({ 840 , 308 }); // EnemyPokemonShadow의 최종 목적지
		FVector2D Curloc = EnemyPokemonShadow->GetComponentLocation();

		if (TargetLocation == Curloc)
		{
			EnemyPokemonShadow->GetComponentLocation() = TargetLocation;
			return;
		}

		Curloc += FVector2D::RIGHT.Half();
		EnemyPokemonShadow->SetComponentLocation(Curloc);
	}

	
}

void APokemonBattleMode::EnemyPokemonUISetting()
{
	FVector2D TargetLocation = FVector2D({ 336 , 166 }); // EnemyPokemonUI의 최종 목적지
	FVector2D Curloc = EnemyPokemonUI->GetComponentLocation();

	Curloc += FVector2D::RIGHT;
	if (TargetLocation == Curloc)
	{
		EnemyPokemonUI->GetComponentLocation() = TargetLocation;
		return;
	}

	EnemyPokemonUI->SetComponentLocation(Curloc);
}

void APokemonBattleMode::PlayerPokemonUISetting()
{
	FVector2D TargetLocation = FVector2D({ 902 , 460 }); // PlayerPokemonUI의 최종 목적지

	FVector2D Curloc = PlayerPokemonUI->GetComponentLocation();

	Curloc += FVector2D::LEFT.Half();
	if (TargetLocation == Curloc)
	{
		PlayerPokemonUI->GetComponentLocation() = TargetLocation;
		return;
	}

	PlayerPokemonUI->SetComponentLocation(Curloc);
}