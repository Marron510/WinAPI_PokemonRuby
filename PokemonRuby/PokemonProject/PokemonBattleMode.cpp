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
	//PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//PlayerRenderer->SetSprite("Player_Throw_MonsterBall.png");

	//PlayerRenderer->CreateAnimation("PlayerThrowMonsterBallReady", "Player_Throw_MonsterBall.png", 0, 0, 0.5f);
	//PlayerRenderer->CreateAnimation("PlayerThrowMonsterBall", "Player_Throw_MonsterBall.png", 0, 3, 0.5f);
	
	//PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBallReady");
	//PlayerRenderer->SetComponentLocation({ 1524 ,416 });
	//PlayerRenderer->SetSpriteScale(1.0f);
	//PlayerRenderer->SetOrder(ERenderOrder::CURSOR);


	/*PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBall");*/
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

		PlayerPokemonShadow = BackImage->GetPlayerPKMShadow();
		EnemyPokemonShadow = BackImage->GetEnemyPokemonShadow();
		PlayerPokemonUI = BackImage->GetPokemonUI();
		EnemyPokemonUI = BackImage->GetEnemyPokemonUI();
	}

	{
		EnemyPokemon = GetWorld()->SpawnActor<AWildPokemon>();
		EnemyPokemon->SetActorLocation({ -132 , 260 });
	}

	{ 
		MyPokemon = GetWorld()->SpawnActor<AMyPokemon>(); 
		MyPokemon->SetActorLocation({ -500, -500});
	}
}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PokemonSetting();

	BattleGroundSetting();

	//PlayerSetting();
	/*ThrowMonsterball();
	SpawnMyPokemon();*/

}


void APokemonBattleMode::PokemonSetting()
{
	
	{
		FVector2D TargetLocation = FVector2D({ 1068 , 260 }); 
		FVector2D Curloc = EnemyPokemon->GetActorLocation();
		Curloc += FVector2D::RIGHT.Half();

		if (TargetLocation == Curloc)
		{
			EnemyPokemon->GetActorLocation() = TargetLocation;
			EnemyPokemonUISetting();
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

//void APokemonBattleMode::PlayerSetting()
//{
//	FVector2D TargetLocation = FVector2D({ 336 ,416 });
//	FVector2D Curloc = PlayerRenderer->GetComponentLocation();
//	Curloc += FVector2D::LEFT.Half();
//
//	if (TargetLocation == Curloc)
//	{
//		PlayerRenderer->GetComponentLocation() = TargetLocation;
//		return;
//	}
//
//	PlayerRenderer->SetComponentLocation(Curloc);
//}
//
//void APokemonBattleMode::ThrowMonsterball()
//{
//	PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBall");
//}
//

void APokemonBattleMode::SpawnMyPokemon()
{
	
	MyPokemon->SetActorLocation({ 336 ,416 });
}