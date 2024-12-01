#include "PreCompile.h"
#include "PokemonBattleMode.h"

#include <EngineBase/EngineTimer.h>
#include <EngineBase/TimeEvent.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>


#include "SelectPokemonMode.h"
#include "LaborProfessorBirchMode.h"
#include "PokemonMath.h"
#include "PokemonBattleMap.h"
#include "MyPokemon.h"
#include "WildPokemon.h"
#include "PokemonText.h"
#include "PokemonEnum.h"
#include "WildPokemon.h"
#include "PokemonHP.h"
#include "PokemonEXP.h"
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
		MonsterBall->SetOrder(ERenderOrder::BackUI);

		MonsterBall->ChangeAnimation("ThrowBallReady");
	}

	UEngineInput::GetInst().DisableInput();

	TimeEventManager.PushEvent(5.0f, [this]()
		{
			UEngineInput::GetInst().EnableInput();
		});
	

}

APokemonBattleMode::~APokemonBattleMode()
{

}

void APokemonBattleMode::BeginPlay()
{
	Super::BeginPlay();

	TimeEventManager.PushEvent(2.0f, [this]()
		{
			DisplayChatText();
		});

	APokemonPreparation();
	{
		EnemyPokemon = GetWorld()->SpawnActor<AWildPokemon>(); 
		EnemyPokemon->SetActorLocation({ -336.0f , 260.0f });
		EnemyPokemon->EncounterWildPokemon(PokemonMapLevel);
		EnemyPokemonLevel = EnemyPokemon->GetLevelStirng();
	}

	{ 
		MyPokemon = GetWorld()->SpawnActor<AMyPokemon>();
		MyPokemon->SetPokemon(GameData::SelectedPokemon);
		MyPokemon->SetActorLocation({ -500.0f, -500.0f });
		MyPokemonName = MyPokemon->GetMyPokemonName();
		MyPokemonLevel = MyPokemon->GetLevelStirng();
	}

	{
		Cursor = GetWorld()->SpawnActor<ACursor>();
		Cursor->SetBattleModeInstance(this);
		CursorRender = Cursor->GetCursorRender();
	}

	{
		ChatText = GetWorld()->SpawnActor<APokemonText>();
		ChatText->SetActorLocation({ 100.0f, 640.0f });
		ChatText->SetTextSpriteName("TextWhite.png");
		ChatText->SetTextScale({ 30, 40 });
		ChatText->SetOrder(ERenderOrder::FONT);
	}

	{
		BattleChatText = GetWorld()->SpawnActor<APokemonText>();
		BattleChatText->SetActorLocation({ 100.0f, 640.0f });
		BattleChatText->SetTextSpriteName("TextWhite.png");
		BattleChatText->SetTextScale({ 30, 40 });
		BattleChatText->SetOrder(ERenderOrder::FONT);
	}

	{
		EnemyPokemonStat = GetWorld()->SpawnActor<APokemonText>();
		EnemyPokemonStat->SetTextSpriteName("TextBlack.png");
		EnemyPokemonStat->SetTextScale({ 26, 36 });
		EnemyPokemonStat->SetText(EnemyPokemon->GetPokemonName());
		EnemyPokemonStat->SetActorLocation({ -600.0f , 135.0f });
		EnemyPokemonStat->SetOrder(ERenderOrder::FONT);

	}

	{
		EnemyPokemonLevelText = GetWorld()->SpawnActor<APokemonText>();
		EnemyPokemonLevelText->SetTextSpriteName("TextBlack.png");
		EnemyPokemonLevelText->SetTextScale({ 26, 36 });
		EnemyPokemonLevelText->SetText(EnemyPokemonLevel);
		EnemyPokemonLevelText->SetActorLocation({ -245.0f , 135.0f });
		EnemyPokemonLevelText->SetOrder(ERenderOrder::FONT);
	}
	{
		
		
		MyPokemonHPText = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonHPText->SetTextSpriteName("TextBlack.png");
		MyPokemonHPText->SetTextScale({ 26, 36 });
		MyPokemonHPText->SetActorLocation({ 1666.0f , 496.0f });
		MyPokemonHPText->SetOrder(ERenderOrder::FONT);
	}
	
	std::string MaxHp = std::to_string(MyPokemon->GetMaxHP());
	{


		MyPokemonMaxHPText = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonMaxHPText->SetTextSpriteName("TextBlack.png");
		MyPokemonMaxHPText->SetTextScale({ 26, 36 });
		MyPokemonMaxHPText->SetText(MaxHp);
		MyPokemonMaxHPText->SetActorLocation({ 1750.0f , 496.0f });
		MyPokemonMaxHPText->SetOrder(ERenderOrder::FONT);
	}
	
	{
		MyPokemonStat = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonStat->SetTextSpriteName("TextBlack.png");
		MyPokemonStat->SetTextScale({ 26, 36 });
		MyPokemonStat->SetText(MyPokemonName);
		MyPokemonStat->SetActorLocation({ 1440.0f , 415.0f });
		MyPokemonStat->SetOrder(ERenderOrder::FONT);
	}

	{
		MyPokemonLevelText = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonLevelText->SetTextSpriteName("TextBlack.png");
		MyPokemonLevelText->SetTextScale({ 26, 36 });
		MyPokemonLevelText->SetText(MyPokemonLevel);
		MyPokemonLevelText->SetActorLocation({ 1775.0f , 415.0f });
		MyPokemonLevelText->SetOrder(ERenderOrder::FONT);
	}


	{
		MyPokemonSkill1 = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonSkill1->SetTextSpriteName("TextBlack.png");
		MyPokemonSkill1->SetTextScale({ 30, 36 });
		MyPokemonSkill1->SetText(MyPokemon->GetSkill1());
		MyPokemonSkill1->SetActorLocation({ 120.0f , 640.0f });
		MyPokemonSkill1->SetOrder(ERenderOrder::FONT);
		
	}

	{
		MyPokemonSkill2 = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonSkill2->SetTextSpriteName("TextBlack.png");
		MyPokemonSkill2->SetTextScale({ 30, 36 });
		MyPokemonSkill2->SetText(MyPokemon->GetSkill2());
		MyPokemonSkill2->SetActorLocation({ 520.0f , 640.0f });
		MyPokemonSkill2->SetOrder(ERenderOrder::FONT);
	}

	{
		MyPokemonSkill3 = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonSkill3->SetTextSpriteName("TextBlack.png");
		MyPokemonSkill3->SetTextScale({ 30, 36 });
		MyPokemonSkill3->SetText(MyPokemon->GetSkill3());
		MyPokemonSkill3->SetActorLocation({ 120.0f , 720.0f });
		MyPokemonSkill3->SetOrder(ERenderOrder::FONT);
	}

	{
		MyPokemonSkill4 = GetWorld()->SpawnActor<APokemonText>();
		MyPokemonSkill4->SetTextSpriteName("TextBlack.png");
		MyPokemonSkill4->SetTextScale({ 30, 36 });
		MyPokemonSkill4->SetText(MyPokemon->GetSkill4());
		MyPokemonSkill4->SetActorLocation({ 520.0f , 720.0f });
		MyPokemonSkill4->SetOrder(ERenderOrder::FONT);
	}

	{
		MyPokemonHPbar = GetWorld()->SpawnActor<APokemonHP>();
		MyPokemonHPbar->SetActorLocation({ 1582.0f, 460.0f });
	}

	{
		EnemyPokemonHPbar = GetWorld()->SpawnActor<APokemonHP>();
		EnemyPokemonHPbar->SetActorLocation({ -445.0f, 185.0f });
	}

	{
		MyPokemonEXP = GetWorld()->SpawnActor<APokemonEXP>();
		MyPokemonEXP->SetActorLocation({ 1506.0f, 535.0f });
	}

	SkillTextOff();

}

void APokemonBattleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	TimeEventManager.Update(_DeltaTime);
	
	

	PokemonSetting();

	BattleGroundSetting();

	PokemonStatUpdate(_DeltaTime);

	PlayerSetting();

	SpawnPokemon(_DeltaTime);
	
	HPCheck(_DeltaTime);

	UpdateEXPBar(_DeltaTime);

	TimeEventManager.PushEvent(4.0f, [this]()
		{
			EnemyPokemonUISetting();
			EnemyPokemonTextSetting();
			EnemyPokemonLevelTextSetting();
			EnemyPokemonHpSetting();
		});

	if (true == IsEnemyPokemonDead)
	{
		TimeEventManager.PushEvent(1.0f, [this]()
			{
				EnemyPokemon->GetRender()->SetOrder(ERenderOrder::POKEMONSHADOW);
				EnemypokemonDead();
			});
		
		TimeEventManager.PushEvent(1.8f, [this]()
			{
				EnemyPokemon->GetRender()->SetActive(false);
			});
	}

	if (true == IsEnemyPokemonDead && false == IsEnemyPokemonDeadEventEnd)
	{
		IsEnemyPokemonDeadEventEnd = true;

		TimeEventManager.PushEvent(1.5f, [this]()
			{
				BGMPlayer = UEngineSound::Play("SEFainted.mp3");
			});
		TimeEventManager.PushEvent(2.5f, [this]()
			{
				ChatText->ClearText();
				ChatText->SetText("Wild " + EnemyPokemon->GetPokemonName() + enter + "fainted!", 0.05f);
			});
		TimeEventManager.PushEvent(6.0f, [this]()
			{
				ChatText->ClearText();
				UEngineSound::AllSoundStop();
				BGMPlayer = UEngineSound::Play("008_ Victory!.mp3");
				int GainedEXP = 15;
				MyPokemon->AddEXP(GainedEXP);
				BGMPlayer = UEngineSound::Play("SEGainExp.mp3");
				ChatText->SetText(MyPokemon->GetMyPokemonName() + " gained" + enter + "15 EXP.Points!", 0.05f);
			});
		TimeEventManager.PushEvent(13.0f, [this]()
			{
				ALaborProfessorBirchMode::LaborProfessorBirchModeChangePos = { 8,4 };
				UEngineSound::AllSoundStop();
				BGMPlayer = UEngineSound::Play("009_ ProfessorBirchsLab.mp3");
				ALaborProfessorBirchMode::ALaborProfessorBirchModePlayerDir = APlayer::EPlayerDir::LEFT_Left_Arm;
				UEngineAPICore::GetCore()->OpenLevel("LaborProfessorBirch");
			});
		
	}
}


void APokemonBattleMode::PokemonSetting()
{
	std::string Hp = std::to_string(MyPokemon->GetHP());
	MyPokemonHPText->SetText(Hp);

	if (bEnemyPokemonPositioned)
	{
		return;
	}

	FVector2D TargetLocation = FVector2D({ 862.0f , 260.0f });
	FVector2D Curloc = EnemyPokemon->GetActorLocation();
	Curloc += FVector2D::RIGHT.Half();

	if (TargetLocation == Curloc)
	{
		EnemyPokemon->GetActorLocation() = TargetLocation;
		

		bEnemyPokemonPositioned = true;
		return;
	}

	EnemyPokemon->SetActorLocation(Curloc);
}

void APokemonBattleMode::APokemonPreparation()
{
	BackImage = GetWorld()->SpawnActor<APokemonBattleMap>();
	Map = BackImage->GetCurMap();

	PlayerPokemonShadow = BackImage->GetPlayerPKMShadow();
	EnemyPokemonShadow = BackImage->GetEnemyPokemonShadow();
	PlayerPokemonUI = BackImage->GetPokemonUI();
	EnemyPokemonUI = BackImage->GetEnemyPokemonUI();
	SelectMenu = BackImage->GetSelectMenu();
	BattleSelectMenu = BackImage->GetBattleSelectMenu();
	BattleText = BackImage->GetBattleText();
}

void APokemonBattleMode::BattleGroundSetting()
{
	if (false == IsPlayerPokemonShadowMoved)
	{
		FVector2D TargetLocation = FVector2D({ 336.0f , 520.0f });
		FVector2D Curloc = PlayerPokemonShadow->GetComponentLocation();
		Curloc += FVector2D::LEFT.Half();

		if (TargetLocation == Curloc)
		{
			PlayerPokemonShadow->SetComponentLocation(TargetLocation);
			IsPlayerPokemonShadowMoved = true;  
			IsBackGroundSetting = true;
			return;
		}

		PlayerPokemonShadow->SetComponentLocation(Curloc);
	}

	if (false == IsEnemyPokemonShadowMoved)
	{
		FVector2D EnemyShadowTargetLocation = FVector2D({ 840.0f , 308.0f });
		FVector2D EnemyCurloc = EnemyPokemonShadow->GetComponentLocation();

		if (EnemyShadowTargetLocation == EnemyCurloc)
		{
			EnemyPokemonShadow->SetComponentLocation(EnemyShadowTargetLocation);
			IsEnemyPokemonShadowMoved = true;  
			return;
		}

		EnemyCurloc += FVector2D::RIGHT.Half();
		EnemyPokemonShadow->SetComponentLocation(EnemyCurloc);
	}
}

void APokemonBattleMode::EnemyPokemonUISetting()
{
	if (false == IsEnemyPokemonUIMoved)
	{
		FVector2D TargetLocation = FVector2D({ 336.0f , 166.0f });
		FVector2D Curloc = EnemyPokemonUI->GetComponentLocation();

		Curloc += FVector2D::RIGHT;

		if (TargetLocation == Curloc)
		{
			EnemyPokemonUI->SetComponentLocation(TargetLocation);
			IsEnemyPokemonUIMoved = true;  
			return;
		}

		EnemyPokemonUI->SetComponentLocation(Curloc);
	}
}

void APokemonBattleMode::EnemyPokemonTextSetting()
{
	if (false == IsEnemyPokemonTextMoved)
	{

		FVector2D TargetLocation = FVector2D({ 130.0f , 135.0f });
		FVector2D Curloc = EnemyPokemonStat->GetActorLocation();

		Curloc += FVector2D::RIGHT;

		if (TargetLocation == Curloc)
		{
			EnemyPokemonStat->GetActorLocation() = TargetLocation;
			IsEnemyPokemonTextMoved = true;
			return;
		}

		EnemyPokemonStat->SetActorLocation(Curloc);
	}
}

void APokemonBattleMode::EnemyPokemonHpSetting()
{
	if (false == IsEnemyPokemonTextMoved)
	{

		FVector2D TargetLocation = FVector2D({ 285.0f , 185.0f });
		FVector2D Curloc = EnemyPokemonHPbar->GetActorLocation();

		Curloc += FVector2D::RIGHT;

		if (TargetLocation == Curloc)
		{
			EnemyPokemonHPbar->GetActorLocation() = TargetLocation;
			IsEnemyPokemonTextMoved = true;
			return;
		}

		EnemyPokemonHPbar->SetActorLocation(Curloc);
	}
}



void APokemonBattleMode::EnemyPokemonLevelTextSetting()
{
	FVector2D TargetLocation = FVector2D({ 485.0f , 135.0f });
	FVector2D Curloc = EnemyPokemonLevelText->GetActorLocation();

	Curloc += FVector2D::RIGHT;

	if (TargetLocation == Curloc)
	{
		EnemyPokemonLevelText->GetActorLocation() = TargetLocation;
		return;
	}

	EnemyPokemonLevelText->SetActorLocation(Curloc);
}

void APokemonBattleMode::PlayerPokemonUISetting()
{
	if (false == IsPlayerPokemonUIMoved)
	{
		FVector2D TargetLocation = FVector2D({ 902.0f , 460.0f });
		FVector2D Curloc = PlayerPokemonUI->GetComponentLocation();

		Curloc += FVector2D::LEFT;

		if (TargetLocation == Curloc)
		{
			PlayerPokemonUI->SetComponentLocation(TargetLocation);
			IsPlayerPokemonUIMoved = true;  
			SpawnSelectMenu();
			return;
		}

		PlayerPokemonUI->SetComponentLocation(Curloc);
	}
}

void APokemonBattleMode::PlayerPokemonTextSetting()
{
	if (false == IsPlayerPokemonTextMoved)
	{
		FVector2D TargetLocation = FVector2D({ 740.0f , 415.0f });
		FVector2D Curloc = MyPokemonStat->GetActorLocation();

		Curloc += FVector2D::LEFT;

		if (TargetLocation == Curloc)
		{
			MyPokemonStat->GetActorLocation() = TargetLocation;
			IsPlayerPokemonTextMoved = true;
			IsChatOn = false;
			return;
		}

		MyPokemonStat->SetActorLocation(Curloc);
	}
	
}


void APokemonBattleMode::PlayerPokemonHPSetting()
{
	if (false == IsPlayerPokemonTextMoved)
	{
		FVector2D TargetLocation = FVector2D({ 882.0f , 460.0f });
		FVector2D Curloc = MyPokemonHPbar->GetActorLocation();

		Curloc += FVector2D::LEFT;

		if (TargetLocation == Curloc)
		{
			MyPokemonHPbar->GetActorLocation() = TargetLocation;
			return;
		}

		MyPokemonHPbar->SetActorLocation(Curloc);
	}

}

void APokemonBattleMode::PlayerPokemonEXPSetting()
{
	if (false == IsPlayerPokemonTextMoved)
	{
		FVector2D TargetLocation = FVector2D({ 806.0f , 535.0f });
		FVector2D Curloc = MyPokemonEXP->GetActorLocation();

		Curloc += FVector2D::LEFT;

		if (TargetLocation == Curloc)
		{
			MyPokemonEXP->GetActorLocation() = TargetLocation;
			return;
		}

		MyPokemonEXP->SetActorLocation(Curloc);
	}

}


void APokemonBattleMode::PlayerPokemonLevelTextSetting()
{
		FVector2D TargetLocation = FVector2D({ 1075.0f , 415.0f });
		FVector2D Curloc = MyPokemonLevelText->GetActorLocation();

		Curloc += FVector2D::LEFT;

		if (TargetLocation == Curloc)
		{
			MyPokemonLevelText->GetActorLocation() = TargetLocation;
			return;
		}

		MyPokemonLevelText->SetActorLocation(Curloc);
}

void APokemonBattleMode::PlayerPokemonHPTextSetting()
{
	FVector2D TargetLocation = FVector2D({ 966.0f , 496.0f });
	FVector2D Curloc = MyPokemonHPText->GetActorLocation();

	Curloc += FVector2D::LEFT;

	if (TargetLocation == Curloc)
	{
		MyPokemonHPText->GetActorLocation() = TargetLocation;
		return;
	}

	MyPokemonHPText->SetActorLocation(Curloc);
}

void APokemonBattleMode::PlayerPokemonMaxHPTextSetting()
{
	FVector2D TargetLocation = FVector2D({ 1050.0f , 496.0f });
	FVector2D Curloc = MyPokemonMaxHPText->GetActorLocation();

	Curloc += FVector2D::LEFT;

	if (TargetLocation == Curloc)
	{
		MyPokemonMaxHPText->GetActorLocation() = TargetLocation;
		return;
	}

	MyPokemonMaxHPText->SetActorLocation(Curloc);
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
		BattleChatText->PrintTextUpdate(_DeltaTime);
	}

	if (UEngineInput::GetInst().IsDown('Z'))
	{
		BGMPlayer = UEngineSound::Play("SEClick.mp3");
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
		PlayerPokemonLevelTextSetting();
		PlayerPokemonHPSetting();
		PlayerPokemonHPTextSetting();
		PlayerPokemonMaxHPTextSetting();
		PlayerPokemonEXPSetting();
	}

}


void APokemonBattleMode::ThrowedMosterBall()
{
	MonsterBall->SetComponentLocation({ 300 , 420 });
}

void APokemonBattleMode::SpawnMyPokemonText()
{
	if (IsChatOn && !IsGoMessageDisplayed)
	{
		ChatText->SetText("Go " + MyPokemonName + "!", 0.01f);
		IsGoMessageDisplayed = true; 
	}
}

void APokemonBattleMode::PokemonStatUpdate(float _DeltaTime)
{
	EnemyPokemonStat->PrintTextUpdate(_DeltaTime);
	MyPokemonStat->PrintTextUpdate(_DeltaTime);
	MyPokemonLevelText->PrintTextUpdate(_DeltaTime);
	EnemyPokemonLevelText->PrintTextUpdate(_DeltaTime);
	MyPokemonMaxHPText->PrintTextUpdate(_DeltaTime);
	MyPokemonHPText->PrintTextUpdate(_DeltaTime);

	if (true == IsBattleNow)
	{
		MyPokemonSkill1->PrintTextUpdate(_DeltaTime);
		MyPokemonSkill2->PrintTextUpdate(_DeltaTime);
		MyPokemonSkill3->PrintTextUpdate(_DeltaTime);
		MyPokemonSkill4->PrintTextUpdate(_DeltaTime);
		BattleChatText->PrintTextUpdate(_DeltaTime);
	}
	
}

void APokemonBattleMode::SpawnSelectMenu()
{
	SelectMenu->SetOrder(ERenderOrder::BackUI1);
	CursorRender->SetOrder(ERenderOrder::CURSOR);
	CursorRender->SetActive(true);
	PlayerRenderer->SetActive(false);
	MonsterBall->SetActive(false);

	ChatText->SetText("What should" + enter + MyPokemonName + " do?", 0.01f);
	
}


void APokemonBattleMode::HandleMenuSelection(FVector2D CursorLocation)
{
	int MenuIndex = -1;

	for (int i = 0; i < 4; i++)
	{
		if (Cursor->GetMenuCursorPosition(i) == CursorLocation)
		{
			MenuIndex = i;
			break;
		}
	}

	if (MenuIndex != -1)
	{
		switch (MenuIndex)
		{
		case 0:

			IsBattleCursorSet = true;

			BattleSelectMenu->SetOrder(ERenderOrder::BackUI2);
			IsBattleNow = true;

			Cursor->SetState(ACursor::ECursorState::Battle);
			ChatText->ClearText();

			if (true == IsBattleCursorSet)
			{
				MyPokemonSkill1->SetActive(true);
				MyPokemonSkill2->SetActive(true);
				MyPokemonSkill3->SetActive(true);
				MyPokemonSkill4->SetActive(true);
				SkillTextOn();
			}

			break;

		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		default:
			break;
		}


	}
}


void APokemonBattleMode::HandleSkillSelection(FVector2D CursorLocation)
{
	int SkillIndex = -1;
	BattleText->SetOrder(ERenderOrder::BackUI3);
	ChatText->SetOrder(ERenderOrder::FONT);
	
	for (int i = 0; i < 4; i++)
	{
		if (Cursor->GetBattleCursorPosition(i) == CursorLocation)
		{
			SkillIndex = i;
			break;
		}
	}

	if (SkillIndex != -1)
	{
		switch (SkillIndex)
		{
		case 0:
			SkillTextOff();
			if ("-" == MyPokemon->GetSkill1())
			{
				FailedSkill();
			}
			else
			{
				PokemonBattleLogic1();
			}
			
			break;
		case 1:
			SkillTextOff();
			if ("-" == MyPokemon->GetSkill2())
			{
				FailedSkill();
			}
			else
			{
				PokemonBattleLogic2();
			}
			break;
		case 2:
			if ("-" == MyPokemon->GetSkill3())
			{
				SkillTextOff();
				FailedSkill();
			}
			else
			{
				MyPokemon->UseSkill(MyPokemon->GetSkill3(), EnemyPokemon);
			}
			break;

		case 3:
			if ("-" == MyPokemon->GetSkill4())
			{
				SkillTextOff();
				FailedSkill();
			}
			else
			{
				MyPokemon->UseSkill(MyPokemon->GetSkill3(), EnemyPokemon);
			}
			break;

		default:
			break;
		}

		
	}
}



void APokemonBattleMode::SkillTextOff()
{
	MyPokemonSkill1->SetOrder(ERenderOrder::WATER);
	MyPokemonSkill2->SetOrder(ERenderOrder::WATER);
	MyPokemonSkill3->SetOrder(ERenderOrder::WATER);
	MyPokemonSkill4->SetOrder(ERenderOrder::WATER);
	CursorRender->SetOrder(ERenderOrder::WATER);
}


void APokemonBattleMode::SkillTextOn()
{
	MyPokemonSkill1->SetOrder(ERenderOrder::FONT);
	MyPokemonSkill2->SetOrder(ERenderOrder::FONT);
	MyPokemonSkill3->SetOrder(ERenderOrder::FONT);
	MyPokemonSkill4->SetOrder(ERenderOrder::FONT);
	CursorRender->SetOrder(ERenderOrder::FONT);
}

void APokemonBattleMode::DisplayChatText()
{
	if (!IsTextDisplayed) 
	{
		ChatText->SetText("Wild " + EnemyPokemon->GetPokemonName() + " appeared!", 0.05f);
		IsTextDisplayed = true;
	}
}

void APokemonBattleMode::Skill1ChatText()
{
	ChatText->SetOrder(ERenderOrder::FONT);
	MyPokemonSkillText = MyPokemon->GetMyPokemonName() + " used" + enter + MyPokemon->GetSkill1() + "!";
	ChatText->SetText(MyPokemonSkillText, 0.1f);
}

void APokemonBattleMode::Skill2ChatText()
{
	ChatText->SetOrder(ERenderOrder::FONT);
	MyPokemonSkillText = MyPokemon->GetMyPokemonName() + " used" + enter + MyPokemon->GetSkill2() + "!";
	ChatText->SetText(MyPokemonSkillText, 0.1f);
}

void APokemonBattleMode::EnemySkill1ChatText()
{
	ChatText->SetOrder(ERenderOrder::FONT);
	ChatText->ClearText();
	EnemyPokemonSkillText = EnemyPokemon->GetPokemonName() + " used" + enter + EnemyPokemon->GetSkill1() + "!";
	ChatText->SetText(EnemyPokemonSkillText, 0.1f);
}

void APokemonBattleMode::PokemonBattleLogic1()
{

	TimeEventManager.PushEvent(0.2f, [this]()
		{
			Skill1ChatText();
			UEngineInput::GetInst().DisableInput();
		});
	TimeEventManager.PushEvent(1.5f, [this]()
		{
			MyPokemon->UseSkill(MyPokemon->GetSkill1(), EnemyPokemon);
		});
	TimeEventManager.PushEvent(2.5f, [this]()
		{
			EnemyDeadCheck();
		});
	
	
}
void APokemonBattleMode::PokemonBattleLogic2()
{
	TimeEventManager.PushEvent(0.2f, [this]()
		{
			Skill2ChatText();
			UEngineInput::GetInst().DisableInput();
		});
	TimeEventManager.PushEvent(1.5f, [this]()
		{
			MyPokemon->UseSkill(MyPokemon->GetSkill2(), EnemyPokemon);
		});
	TimeEventManager.PushEvent(3.0f, [this]()
		{
			EnemySkill1ChatText();
		});
	
}

void APokemonBattleMode::FailedSkill()
{
	TimeEventManager.PushEvent(0.1f, [this]()
		{
			ChatText->SetText("But it failed!");
		});
	TimeEventManager.PushEvent(1.0f, [this]()
		{
			ChatText->ClearText();
			BattleText->SetOrder(ERenderOrder::BackUI1);
			SkillTextOn();
		});
	

}



void APokemonBattleMode::HPCheck(float _DeltaTime)
{
	static FVector2D MyCurrentHPBarScale = MyPokemonHPbar->GetRender()->GetComponentScale();
	static FVector2D EnemyCurrentHPBarScale = EnemyPokemonHPbar->GetRender()->GetComponentScale();

	float TargetMyPokemonHPScaleX = UEngineMath::Clamp(static_cast<float>(MyPokemon->GetHP()) / MyPokemon->GetMaxHP(), 0.0f, 1.0f) * 230.0f;
	float TargetEnemyPokemonHPScaleX = UEngineMath::Clamp(static_cast<float>(EnemyPokemon->GetHP()) / EnemyPokemon->GetMaxHP(), 0.0f, 1.0f) * 230.0f;

	FVector2D TargetMyHPBarScale(TargetMyPokemonHPScaleX, 14.0f);
	FVector2D TargetEnemyHPBarScale(TargetEnemyPokemonHPScaleX, 16.0f);

	float AnimationSpeed = 300.0f; 

	if (MyCurrentHPBarScale.X > TargetMyHPBarScale.X)
	{
		MyCurrentHPBarScale.X -= AnimationSpeed * _DeltaTime;
		if (MyCurrentHPBarScale.X < TargetMyHPBarScale.X) 
		{
			MyCurrentHPBarScale.X = TargetMyHPBarScale.X;
		}
	}
	else if (MyCurrentHPBarScale.X < TargetMyHPBarScale.X)
	{
		MyCurrentHPBarScale.X += AnimationSpeed * _DeltaTime;
		if (MyCurrentHPBarScale.X > TargetMyHPBarScale.X)
		{
			MyCurrentHPBarScale.X = TargetMyHPBarScale.X;
		}
	}

	MyPokemonHPbar->GetRender()->SetComponentScale(MyCurrentHPBarScale);

	if (EnemyCurrentHPBarScale.X > TargetEnemyHPBarScale.X)
	{
		EnemyCurrentHPBarScale.X -= AnimationSpeed * _DeltaTime;
		if (EnemyCurrentHPBarScale.X < TargetEnemyHPBarScale.X)
		{
			EnemyCurrentHPBarScale.X = TargetEnemyHPBarScale.X;
		}
	}
	else if (EnemyCurrentHPBarScale.X < TargetEnemyHPBarScale.X)
	{
		EnemyCurrentHPBarScale.X += AnimationSpeed * _DeltaTime;
		if (EnemyCurrentHPBarScale.X > TargetEnemyHPBarScale.X)
		{
			EnemyCurrentHPBarScale.X = TargetEnemyHPBarScale.X;
		}
	}

	EnemyPokemonHPbar->GetRender()->SetComponentScale(EnemyCurrentHPBarScale);
}




void APokemonBattleMode::EnemyPokemonAttack()
{
	TimeEventManager.PushEvent(1.0f, [this]()
		{
			EnemySkill1ChatText();
		});
	TimeEventManager.PushEvent(2.5f, [this]()
		{
			EnemyPokemon->UseSkill(EnemyPokemon->GetSkill1(), MyPokemon);
		});
	TimeEventManager.PushEvent(4.0f, [this]()
		{
			ChatText->ClearText();
			SpawnSelectMenu();
			SkillTextOff();
			BattleText->SetOrder(ERenderOrder::BackUI);
			BattleSelectMenu->SetOrder(ERenderOrder::BackUI);
			Cursor->SetState(ACursor::ECursorState::Menu);
			CursorRender->SetOrder(ERenderOrder::CURSOR);
			UEngineInput::GetInst().EnableInput();
		});
}
void APokemonBattleMode::EnemyDeadCheck()
{
	if (0 >= EnemyPokemon->GetHP())
	{
		TimeEventManager.PushEvent(1.0f, [this]()
			{
				IsEnemyPokemonDead = true;
			});
	}
	else
	{
		EnemyPokemonAttack();
	}
}
void APokemonBattleMode::EnemypokemonDead()
{
	{
		FVector2D TargetLocation = FVector2D({ 862.0f , 550.0f });
		FVector2D Curloc = EnemyPokemon->GetActorLocation();
		Curloc += FVector2D::DOWN.Half();

		if (TargetLocation == Curloc)
		{
			EnemyPokemon->GetActorLocation() = TargetLocation;
			EnemyPokemon->GetRender()->SetActive(false);
			return;
		}

		EnemyPokemon->SetActorLocation(Curloc);
	}
}



void APokemonBattleMode::UpdateEXPBar(float _DeltaTime)
{
	static FVector2D CurrentEXPBarScale = MyPokemonEXP->GetRender()->GetComponentScale();

	float TargetEXPScaleX = UEngineMath::Clamp(static_cast<float>(MyPokemon->GetEXP()) / MyPokemon->GetMaxEXP(), 0.0f, 1.0f) * 230.0f;

	FVector2D TargetEXPBarScale(TargetEXPScaleX, 9.0f);

	float AnimationSpeed = 100.0f; 

	if (CurrentEXPBarScale.X > TargetEXPBarScale.X)
	{
		CurrentEXPBarScale.X -= AnimationSpeed * _DeltaTime;
		if (CurrentEXPBarScale.X < TargetEXPBarScale.X) 
		{
			CurrentEXPBarScale.X = TargetEXPBarScale.X;
		}
	}
	else if (CurrentEXPBarScale.X < TargetEXPBarScale.X)
	{
		CurrentEXPBarScale.X += AnimationSpeed * _DeltaTime;
		if (CurrentEXPBarScale.X > TargetEXPBarScale.X) 
		{
			CurrentEXPBarScale.X = TargetEXPBarScale.X;
		}
	}

	MyPokemonEXP->GetRender()->SetComponentScale({ CurrentEXPBarScale.X, TargetEXPBarScale.Y });
}
