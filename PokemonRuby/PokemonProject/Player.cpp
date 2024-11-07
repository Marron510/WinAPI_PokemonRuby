#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonMapMode.h"
#include "PokemonEnum.h"
#include "PokemonMath.h"




APlayer::APlayer()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		
		SpriteRenderer->SetSprite("Player_Walk_Up.png");
		SpriteRenderer->SetSprite("Player_Walk_Down.png");
		SpriteRenderer->SetSprite("Player_Walk_Right.png");
		SpriteRenderer->SetSprite("Player_Walk_Left.png");

		SpriteRenderer->SetComponentScale({ 300, 300 });

		SpriteRenderer->CreateAnimation("Walk_Up", "Player_Walk_Up.png", 0, 4, 0.2f);
		SpriteRenderer->CreateAnimation("Walk_Down", "Player_Walk_Down.png", 0, 4, 0.2f);
		SpriteRenderer->CreateAnimation("Walk_Right", "Player_Walk_Right.png", 0, 4, 0.2f);
		SpriteRenderer->CreateAnimation("Walk_Left", "Player_Walk_Left.png", 0, 4, 0.2f);



		SpriteRenderer->CreateAnimation("Idle_Up", "Player_Walk_Up.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Down", "Player_Walk_Down.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Left", "Player_Walk_Left.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Walk_Right.png", 0, 0, 0.1f);


	}
}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	Super::BeginPlay();
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
	GetWorld()->SetCameraToMainPawn(false);
	SpriteRenderer->SetOrder(ERenderOrder::PLAYER);
	AGameMode* Curmode = UEngineAPICore::GetCore()->GetCurLevel()->GetGameMode();
	SpriteMapRenderer = Curmode->Map;
	MapSize = SpriteMapRenderer->GetComponentScale();
	CurPos = { MapSize.Half().TileVector().X, MapSize.Half().TileVector().Y };
	SetActorLocationTile(CurPos);
}


void APlayer::Tick(float _DeltaTime)
{	
	Super::Tick(_DeltaTime);

	PlayerCameraCheck();
	PlayerDebugCheck(_DeltaTime);
	
}


void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}


void APlayer::SetObject(FVector2D _location)
{
	FVector2D ObjectLocation = _location;
	ObjectLocation.operator*(96);
	int LocationX = static_cast<int>(ObjectLocation.iX());
	int LocationY = static_cast<int>(ObjectLocation.iY());

	SetActorLocation({ LocationX , LocationY });
}


void APlayer::SetActorLocationTile(FVector2D _location)
{
	FVector2D Newloacation = _location.operator*(96);
	Newloacation.X += 48;
	Newloacation.Y += 48;
	SetActorLocation(Newloacation);
}



FVector2D APlayer::TileLerp(FVector2D _Start, FVector2D _End, float _t)
{
	return Lerp(_Start, _End, _t);
}


FVector2D APlayer::Lerp(const FVector2D& _Start, const FVector2D& _End, float _t)
{
	if (_t <= 0.0f)
	{
		return _Start;
	}

	if (_t >= 1.0f)
	{
		return _End;
	}

	return _Start + ((_End - _Start) * _t);
}

void APlayer::PlayerCameraCheck()
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FVector2D MapEnd = MapSize - Size;
	GetWorld()->SetCameraPos(GetActorLocation() - Size.Half());
	FVector2D CamPos = GetWorld()->GetCameraPos();
	if (0 >= CamPos.X)
	{
		CamPos.X = 0.0f;
	}
	if (MapEnd.X <= CamPos.X)
	{
		CamPos.X = MapEnd.X;
	}
	if (0 >= MapEnd.X)
	{
		CamPos.X = MapSize.Half().X - Size.Half().X;
	}
	if (0 >= CamPos.Y)
	{
		CamPos.Y = 0.0f;
	}
	if (MapEnd.Y <= CamPos.Y)
	{
		CamPos.Y = MapEnd.Y;
	}if (0 >= MapEnd.Y)
	{
		CamPos.Y = MapSize.Half().Y - Size.Half().Y;
	}

}
void APlayer::PlayerDebugCheck(float _DeltaTime)
{
	FVector2D CamPos = GetWorld()->GetCameraPos();
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().operator/(96).ToString());
	UEngineDebug::CoreOutPutString("CamPos : " + CamPos.ToString());
}


void APlayer::StateUpdate(float _DeltaTime)
{
	switch (CurPlayerState)
	{
	case APlayerState::None:
		StateChange(APlayerState::Idle);
		break;
	case APlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case APlayerState::Walk:
		Walk(_DeltaTime);
		break;
	case APlayerState::Run:
		Walk(_DeltaTime);
		break;
	case APlayerState::Jump:
		Jump(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::StateChange(APlayerState _State, bool _Restart)
{
	if (false == _Restart && CurPlayerState == _State)
	{
		return;
	}

	switch (_State)
	{
	case APlayerState::Idle:
		IdleStart();
		break;
	case APlayerState::Walk:
		WalkStart();
		break;
	case APlayerState::Run:
		WalkStart();
		break;
	case APlayerState::Jump:
		JumpStart();
		break;
	default:
		break;
	}

	CurPlayerState = _State;
}

void APlayer::ChangeAnimation(APlayerState _State)
{
	switch (_State)
	{
	case APlayerState::Idle:
		SpriteRenderer->ChangeAnimation("Idle_Down");
		break;
	case APlayerState::Walk:
		SpriteRenderer->ChangeAnimation("Walk_Down");
		break;
	
	default:
		break;
	}

}