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
#include "PokemonText.h"
#include "PokemonEnum.h"





APokemonBattleMode::APokemonBattleMode()
{
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PlayerRenderer->SetSprite("Player_Throw_MonsterBall.png");

	PlayerRenderer->CreateAnimation("PlayerThrowMonsterBallReady", "Player_Throw_MonsterBall.png", 0, 0, 0.5f);
	PlayerRenderer->CreateAnimation("PlayerThrowMonsterBall", "Player_Throw_MonsterBall.png", 0, 3, 0.1f, false);

	PlayerRenderer->SetComponentLocation({ 1524 ,416 });
	PlayerRenderer->SetSpriteScale(1.0f);
	PlayerRenderer->SetOrder(ERenderOrder::CURSOR);

	PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBallReady");

	MonsterBall = CreateDefaultSubObject<USpriteRenderer>();
	MonsterBall->SetSprite("ThrowBall.png");
	
	MonsterBall->CreateAnimation("ThrowBallReady", "ThrowBall.png", 0, 0, 0.1f);
	MonsterBall->CreateAnimation("ThrowBall", "ThrowBall.png", 5, 61, 0.03f, false);
	
	
	MonsterBall->SetSpriteScale(1.0f);
	MonsterBall->SetOrder(ERenderOrder::UI);

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
		TextWhite = GetWorld()->SpawnActor<APokemonText>();
		TextWhite->SetActorLocation({ 100, 640 });
		TextWhite->SetTextSpriteName("TextWhite.png");
		TextWhite->SetTextScale({ 30, 40 });
		TextWhite->SetText("Wild Zigzagoon Appeared!", 0.05f);
		TextWhite->SetOrder(ERenderOrder::FONT);
	}

	{
		TextBlack = GetWorld()->SpawnActor<APokemonText>();
		TextBlack->SetTextSpriteName("TextBlack.png");
		TextBlack->SetTextScale({ 25, 30 });
		TextBlack->SetText("POOCHANA");
		TextBlack->SetActorLocation({ -600 , 135 });
		TextBlack->SetOrder(ERenderOrder::FONT);
	}


}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	PokemonSetting();

	BattleGroundSetting();
	

	PlayerSetting();

	TextBlack->PrintTextUpdate(_DeltaTime);

	if (true == IsPlayerSetting)
	{
	TextWhite->PrintTextUpdate(_DeltaTime);
	}

	if (UEngineInput::GetInst().IsDown('Z'))
	{
		ThrowMonsterball();
		MonsterBall->ChangeAnimation("ThrowBall");
		if (0 > PlayerLocation.X)
		{
			IsThrowing = true;
		}
	}
	
	if (true == IsThrowing)
	{
		MonsterBall->SetComponentLocation({ 200 ,432 }); 
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
			EnemyPokemonTextSetting();
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

	if (TargetLocation == Curloc)
	{
		TextBlack->GetActorLocation() = TargetLocation;
	}

	EnemyPokemonUI->SetComponentLocation(Curloc);
}

void APokemonBattleMode::EnemyPokemonTextSetting()
{
	FVector2D TargetLocation = FVector2D({ 130 , 135 }); // EnemyPokemonUI의 최종 목적지
	FVector2D Curloc = TextBlack->GetActorLocation();

	Curloc += FVector2D::RIGHT;
	
	if (TargetLocation == Curloc)
	{
		TextBlack->GetActorLocation() = TargetLocation;
		return;
	}

	TextBlack->SetActorLocation(Curloc);
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
		ThrowedMosterBall();
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
	float LocX = PlayerLocation.X;
	PlayerRenderer->SetComponentLocation(PlayerLocation);
	
	if (-100 > LocX)
	{
		SpawnMyPokemon();
	}
}


void APokemonBattleMode::SpawnMyPokemon()
{
	
	MyPokemon->SetActorLocation({ 336 ,416 });
}


void APokemonBattleMode::ThrowedMosterBall()
{
	MonsterBall->SetComponentLocation({ 300 , 420 });
	
}

