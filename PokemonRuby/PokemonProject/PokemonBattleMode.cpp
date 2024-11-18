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
#include "PokemonFont.h"
#include "PokemonEnum.h"





APokemonBattleMode::APokemonBattleMode()
{
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PlayerRenderer->SetSprite("Player_Throw_MonsterBall.png");

	PlayerRenderer->CreateAnimation("PlayerThrowMonsterBallReady", "Player_Throw_MonsterBall.png", 0, 0, 0.5f);
	PlayerRenderer->CreateAnimation("PlayerThrowMonsterBall", "Player_Throw_MonsterBall.png", 0, 3, 0.15f, false);

	PlayerRenderer->SetComponentLocation({ 1524 ,416 });
	PlayerRenderer->SetSpriteScale(1.0f);
	PlayerRenderer->SetOrder(ERenderOrder::CURSOR);

	PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBallReady");

	MonsterBall = CreateDefaultSubObject<USpriteRenderer>();
	MonsterBall->SetSprite("ThrowBall.png");
	
	MonsterBall->CreateAnimation("ThrowBallReady", "ThrowBall.png", 0, 0, 0.1f);
	MonsterBall->CreateAnimation("ThrowBall", "ThrowBall.png", 0, 42, 0.03f, false);
	
	
	MonsterBall->SetSpriteScale(1.0f);
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
		MyPokemon = GetWorld()->SpawnActor<AMyPokemon>(); // 내 포켓몬 추가
		MyPokemon->SetActorLocation({ -500, -500});
	}
	
	{
		Font = GetWorld()->SpawnActor<APokemonFont>();
		Font->SetActorLocation({ 100, 640 });
		Font->SetTextSpriteName("Font.png");
		Font->SetOrder(ERenderOrder::FONT);
		Font->SetTextScale({ 40, 40 });
		Font->SetFont("HELLOMYPOKEMONSKEMDIEKDMIEKDM", 0.1f);

	}

}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PokemonSetting();

	BattleGroundSetting();

	PlayerSetting();

	if (true == IsPlayerSetting)
	{
		
	}

	if (UEngineInput::GetInst().IsDown('Z'))
	{
		ThrowMonsterball();
		
		if (0 > PlayerLocation.X)
		{
			IsThrowing = true;
		}
	}
	
	if (true == IsThrowing)
	{
		MonsterBall->SetComponentLocation({ 200 ,432 }); // 336 까지
		MonsterBall->ChangeAnimation("ThrowBall");
		ThrowedMosterBall();
	}
	
}


void APokemonBattleMode::PokemonSetting()
{
	
	{
		FVector2D TargetLocation = FVector2D({ 1054 , 260 }); 
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
		FVector2D EnemyShadowTargetLocation = FVector2D({ 840 , 308 }); // EnemyPokemonShadow의 최종 목적지
		FVector2D EnemyCurloc = EnemyPokemonShadow->GetComponentLocation();

		if (EnemyShadowTargetLocation == EnemyCurloc)
		{
			EnemyPokemonShadow->GetComponentLocation() = EnemyShadowTargetLocation;
			return;
		}

		EnemyCurloc += FVector2D::RIGHT.Half();
		EnemyPokemonShadow->SetComponentLocation(EnemyCurloc);
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
		IsPlayerSetting = true;
		return;
	}

	PlayerRenderer->SetComponentLocation(Curloc);

	

}

void APokemonBattleMode::ThrowMonsterball()
{

	PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBall");
	FVector2D PlayerLocation = PlayerRenderer->GetComponentLocation();
	PlayerLocation += FVector2D::LEFT * 2;
	PlayerRenderer->SetComponentLocation(PlayerLocation);
	
}


void APokemonBattleMode::SpawnMyPokemon()
{
	
	MyPokemon->SetActorLocation({ 336 ,416 });
}


void APokemonBattleMode::ThrowedMosterBall()
{

	
	
	
}
