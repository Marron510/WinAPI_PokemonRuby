#include "PreCompile.h"
#include "PokemonBattleMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>



#include "PokemonMath.h"
#include "PokemonBattleMap.h"
#include "MyPokemon.h"
#include "WildPokemon.h"






APokemonBattleMode::APokemonBattleMode()
{
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PlayerRenderer->SetSprite("Player_Throw_MonsterBall.png");

	PlayerRenderer->CreateAnimation("PlayerThrowMonsterBallReady", "Player_Throw_MonsterBall.png", 0, 0, 0.5f);
	PlayerRenderer->CreateAnimation("PlayerThrowMonsterBall", "Player_Throw_MonsterBall.png", 0, 3, 0.175f, false);

	PlayerRenderer->SetComponentLocation({ 1524 ,416 });
	PlayerRenderer->SetSpriteScale(1.0f);
	PlayerRenderer->SetOrder(ERenderOrder::CURSOR);

	PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBallReady");

	MonsterBall = CreateDefaultSubObject<USpriteRenderer>();
	
	MonsterBall->SetSprite("ThrowBall.png");
	MonsterBall->CreateAnimation("ThrowBallReady", "ThrowBall.png", 0, 0, 0.1f);
	MonsterBall->CreateAnimation("ThrowBall", "ThrowBall.png", 0, 42, 0.1f, false);
	MonsterBall->SetSpriteScale(1.0f);
	MonsterBall->SetComponentLocation({ -500 ,-500 });

	MonsterBall->SetOrder(ERenderOrder::CURSOR);
	MonsterBall->ChangeAnimation("ThrowBallReady");

}

APokemonBattleMode::~APokemonBattleMode()
{

}

void APokemonBattleMode::BeginPlay()
{
	Super::BeginPlay();

	

	SetBackGround();

	{
		EnemyPokemon = GetWorld()->SpawnActor<AWildPokemon>(); // 적 포켓몬 추가
		EnemyPokemon->SetActorLocation({ -132 , 260 });
	}

	{ 
		MyPokemon = GetWorld()->SpawnActor<AMyPokemon>(); // 내 포켄몬 추가
		MyPokemon->SetActorLocation({ -500, -500});
	}
}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PokemonSetting();

	BattleGroundSetting();

	PlayerSetting();

	if (UEngineInput::GetInst().IsDown('Z'))
	{
		ThrowMonsterball();
		ThrowedMosterBall();
	}

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

void APokemonBattleMode::SetBackGround()
{
	APokemonBattleMap* BackImage = GetWorld()->SpawnActor<APokemonBattleMap>();
	Map = BackImage->GetCurMap();

	PlayerPokemonShadow = BackImage->GetPlayerPKMShadow();
	EnemyPokemonShadow = BackImage->GetEnemyPokemonShadow();
	PlayerPokemonUI = BackImage->GetPokemonUI();
	EnemyPokemonUI = BackImage->GetEnemyPokemonUI();
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

void APokemonBattleMode::PlayerSetting()
{
	FVector2D TargetLocation = FVector2D({ 336 ,416 });
	FVector2D Curloc = PlayerRenderer->GetComponentLocation();
	Curloc += FVector2D::LEFT.Half();

	if (TargetLocation == Curloc)
	{
		PlayerRenderer->GetComponentLocation() = TargetLocation;
		
		return;
	}

	PlayerRenderer->SetComponentLocation(Curloc);

	

}

void APokemonBattleMode::ThrowMonsterball()
{

	PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBall");
	FVector2D Curloc = PlayerRenderer->GetComponentLocation();
	Curloc += FVector2D::LEFT;
	PlayerRenderer->SetComponentLocation(Curloc);
}


void APokemonBattleMode::SpawnMyPokemon()
{
	
	MyPokemon->SetActorLocation({ 336 ,416 });
}

void APokemonBattleMode::ThrowedMosterBall()
{
	MonsterBall->SetComponentLocation({ 0 ,416 }); // 336 까지
	FVector2D Curloc = MonsterBall->GetComponentLocation();
	FVector2D Targetloc = FVector2D({ 336 , 900 });
	MonsterBall->ChangeAnimation("ThrowBall");
	Curloc += FVector2D::RIGHT * 5;

	if (Targetloc.X <= Curloc.X)
	{
		MonsterBall->SetComponentLocation(Targetloc);
	}
	MonsterBall->SetComponentLocation(Curloc);
}