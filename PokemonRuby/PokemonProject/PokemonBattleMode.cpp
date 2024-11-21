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
#include "WildPokemon.h"
#include "Cursor.h"




APokemonBattleMode::APokemonBattleMode()
{
	{
		PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
		PlayerRenderer->SetSprite("Player_Throw_MonsterBall.png");

		PlayerRenderer->CreateAnimation("PlayerThrowMonsterBallReady", "Player_Throw_MonsterBall.png", 0, 0, 0.5f);
		PlayerRenderer->CreateAnimation("PlayerThrowMonsterBall", "Player_Throw_MonsterBall.png", 0, 3, 0.1f, false);
		PlayerRenderer->CreateAnimation("PlayerThrowMonsterBallEnd", "Player_Throw_MonsterBall.png", 3, 3, 0.1f);

		PlayerRenderer->SetComponentLocation({ 1524.0f ,416.0f });
		PlayerRenderer->SetSpriteScale(1.0f);
		PlayerRenderer->SetOrder(ERenderOrder::CURSOR);

		PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBallReady");
	}

	{
		MonsterBall = CreateDefaultSubObject<USpriteRenderer>();
		MonsterBall->SetSprite("ThrowBall.png");

		MonsterBall->CreateAnimation("ThrowBallReady", "ThrowBall.png", 0, 0, 0.1f);
		MonsterBall->CreateAnimation("ThrowBall", "ThrowBall.png", 5, 61, 0.025f, false);


		MonsterBall->SetSpriteScale(1.0f);
		MonsterBall->SetOrder(ERenderOrder::UI);

		MonsterBall->ChangeAnimation("ThrowBallReady");
	}
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
		EnemyPokemon->SetActorLocation({ -312.0f , 260.0f });
		EnemyPokemon->EncounterWildPokemon(PokemonMapLevel);
	}

	{ 
		MyPokemon = GetWorld()->SpawnActor<AMyPokemon>(); // 내 포켓몬 추가
		MyPokemon->SetActorLocation({ -500.0f, -500.0f });
	}

	{
		Cursor = GetWorld()->SpawnActor<ACursor>();
		CursorRender = Cursor->GetCursorRender();
	}

	{
		ChatText = GetWorld()->SpawnActor<APokemonText>();
		ChatText->SetActorLocation({ 100.0f, 640.0f });
		ChatText->SetTextSpriteName("TextWhite.png");
		ChatText->SetTextScale({ 30, 40 });
		ChatText->SetText("Wild "+ EnemyPokemon->GetPokemonName() + " appeard!", 0.05f);
		ChatText->SetOrder(ERenderOrder::FONT);
	}

	{
		EnemyPokemonStat = GetWorld()->SpawnActor<APokemonText>();
		EnemyPokemonStat->SetTextSpriteName("TextBlack.png");
		EnemyPokemonStat->SetTextScale({ 25, 30 });
		EnemyPokemonStat->SetText(EnemyPokemon->GetPokemonName());
		EnemyPokemonStat->SetActorLocation({ -600.0f , 135.0f });
		EnemyPokemonStat->SetOrder(ERenderOrder::FONT);

	}

	{
		MyPokemonStat = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonStat->SetTextSpriteName("TextBlack.png");
		MyPokemonStat->SetTextScale({ 25, 30 });
		MyPokemonStat->SetText("TREEKO");
		MyPokemonStat->SetActorLocation({ 1440.0f , 415.0f });
		MyPokemonStat->SetOrder(ERenderOrder::FONT);
	}

}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	

	PokemonSetting();

	BattleGroundSetting();
	
	PokemonStatUpdate(_DeltaTime);

	PlayerSetting();

	SpawnPokemon(_DeltaTime);
	
	
}


void APokemonBattleMode::PokemonSetting()
{
	
	{
		FVector2D TargetLocation = FVector2D({ 862.0f , 260.0f }); 
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
	SelectMenu = BackImage->GetSelectMenu();
	BattleSelectMenu = BackImage->GetBattleSelectMenu();
}


void APokemonBattleMode::BattleGroundSetting()
{
	
	
	{
		FVector2D TargetLocation = FVector2D({ 336.0f , 520.0f }); // PlayerPokemonShadow의 최종 목적지
		FVector2D Curloc = PlayerPokemonShadow->GetComponentLocation();
		Curloc += FVector2D::LEFT.Half();
		if (TargetLocation == Curloc)
		{
			PlayerPokemonShadow->GetComponentLocation() = TargetLocation;
			IsBackGroundSetting = true;
			return;
		}

		PlayerPokemonShadow->SetComponentLocation(Curloc);
	}

	{
		FVector2D EnemyShadowTargetLocation = FVector2D({ 840.0f , 308.0f }); // EnemyPokemonShadow의 최종 목적지
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
	FVector2D TargetLocation = FVector2D({ 336.0f , 166.0f }); // EnemyPokemonUI의 최종 목적지
	FVector2D Curloc = EnemyPokemonUI->GetComponentLocation();

	Curloc += FVector2D::RIGHT;
	if (TargetLocation == Curloc)
	{
		EnemyPokemonUI->GetComponentLocation() = TargetLocation;
		return;
	}

	EnemyPokemonUI->SetComponentLocation(Curloc);
}

void APokemonBattleMode::EnemyPokemonTextSetting()
{
	FVector2D TargetLocation = FVector2D({ 130.0f , 135.0f }); 
	FVector2D Curloc = EnemyPokemonStat->GetActorLocation();

	Curloc += FVector2D::RIGHT;
	
	if (TargetLocation == Curloc)
	{
		EnemyPokemonStat->GetActorLocation() = TargetLocation;
		return;
	}

	EnemyPokemonStat->SetActorLocation(Curloc);
}


void APokemonBattleMode::PlayerPokemonUISetting()
{
	FVector2D TargetLocation = FVector2D({ 902.0f , 460.0f }); // PlayerPokemonUI의 최종 목적지
	FVector2D Curloc = PlayerPokemonUI->GetComponentLocation();

	Curloc += FVector2D::LEFT;
	
	if (TargetLocation == Curloc)
	{
		PlayerPokemonUI->GetComponentLocation() = TargetLocation;
		
		return;
	}

	PlayerPokemonUI->SetComponentLocation(Curloc);
}

void APokemonBattleMode::PlayerPokemonTextSetting()
{
	FVector2D TargetLocation = FVector2D({ 740.0f , 415.0f });
	FVector2D Curloc = MyPokemonStat->GetActorLocation();
	
	Curloc += FVector2D::LEFT;

	if (TargetLocation == Curloc)
	{
		MyPokemonStat->GetActorLocation() = TargetLocation;
		IsChatOn = false;
		SpawnSelectMenu();
		return;
	}

	MyPokemonStat->SetActorLocation(Curloc);
}



void APokemonBattleMode::PlayerSetting()
{
	FVector2D TargetLocation = FVector2D({ 336.0f ,416.0f });
	PlayerLocation = PlayerRenderer->GetComponentLocation();
	PlayerLocation += FVector2D::LEFT.Half();

	if (TargetLocation == PlayerLocation)
	{
		PlayerRenderer->GetComponentLocation() = TargetLocation;
		return;
	}

	PlayerRenderer->SetComponentLocation(PlayerLocation);

	

}

void APokemonBattleMode::ThrowMonsterball()
{
	FVector2D TargetLocation = FVector2D({ -100.0f ,416.0f });
	PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBall");
	PlayerLocation = PlayerRenderer->GetComponentLocation();
	PlayerLocation += FVector2D::LEFT * 2;
	PlayerRenderer->SetComponentLocation(PlayerLocation);
	IsChatOn = true;
}

void APokemonBattleMode::SpawnPokemon(float _DeltaTime)
{
	if (true == IsBackGroundSetting)
	{
		ChatText->PrintTextUpdate(_DeltaTime);
	}

	if (UEngineInput::GetInst().IsDown('Z'))
	{
		ThrowMonsterball();
		MonsterBall->ChangeAnimation("ThrowBall");
		ThrowedMosterBall();
	}

	SpawnMyPokemonText();
	SpawnMyPokemon();


}

void APokemonBattleMode::SpawnMyPokemon()
{
	if (-300 > PlayerLocation.X)
	{
		MyPokemon->SetActorLocation({ 336 ,416 });
		PlayerRenderer->SetActive(false);
		PlayerPokemonUISetting();
		PlayerPokemonTextSetting();
	}

}


void APokemonBattleMode::ThrowedMosterBall()
{
	MonsterBall->SetComponentLocation({ 300 , 420 });
}

void APokemonBattleMode::SpawnMyPokemonText()
{
	if (IsChatOn == true)
	{
		ChatText->SetText("Go Treeko!", 0.01f);
	}
}

void APokemonBattleMode::PokemonStatUpdate(float _DeltaTime)
{
	EnemyPokemonStat->PrintTextUpdate(_DeltaTime);
	MyPokemonStat->PrintTextUpdate(_DeltaTime);
}



void APokemonBattleMode::SpawnSelectMenu()
{
	SelectMenu->SetOrder(ERenderOrder::UI);
	std::string enter = "\n";
	ChatText->SetText("What should"+ enter +"TREEKO do? ", 0.01f);

	CursorRender->SetActive(true);
}



void APokemonBattleMode::SpawnBattleSelectMenu()
{
	BattleSelectMenu->SetOrder(ERenderOrder::UI);
}