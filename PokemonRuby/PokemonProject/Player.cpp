#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonMapMode.h"
#include "PokemonEnum.h"




APlayer::APlayer()
{

	SetActorLocationTile({ 94,70 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		
		SpriteRenderer->SetSprite("Player_Walk_Up.png");
		SpriteRenderer->SetSprite("Player_Walk_Down.png");
		SpriteRenderer->SetSprite("Player_Walk_Right.png");
		SpriteRenderer->SetSprite("Player_Walk_Left.png");

		SpriteRenderer->SetComponentScale({ 300, 300 });

		SpriteRenderer->CreateAnimation("Walk_Up", "Player_Walk_Up.png", 0, 4, 0.3f);
		SpriteRenderer->CreateAnimation("Walk_Down", "Player_Walk_Down.png", 0, 4, 0.3f);
		SpriteRenderer->CreateAnimation("Walk_Right", "Player_Walk_Right.png", 0, 4, 0.3f);
		SpriteRenderer->CreateAnimation("Walk_Left", "Player_Walk_Left.png", 0, 4, 0.3f);



		SpriteRenderer->CreateAnimation("Idle_Up", "Player_Walk_Up.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Down", "Player_Walk_Down.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Left", "Player_Walk_Left.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Walk_Right.png", 0, 0, 0.1f);

		SpriteRenderer->ChangeAnimation("Idle_Down");

	

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

	
	
}


void APlayer::Tick(float _DeltaTime)
{
	
	Super::Tick(_DeltaTime);
	
	
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPos(GetActorLocation() - Size.Half());

	FVector2D CamPos = GetWorld()->GetCameraPos();
	if (0 >= CamPos.X)
	{
		CamPos.X = 0.0f;
	}
	if (9550 <= CamPos.X)
	{
		CamPos.X = 9550.0f;
	}
	if (0 >= CamPos.Y)
	{
		CamPos.Y = 0.0f;
	}
	if (7060 <= CamPos.Y)
	{
		CamPos.Y = 7060.0f;
	}


	GetWorld()->SetCameraPos(CamPos);


	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().operator/(96).ToString());
	UEngineDebug::CoreOutPutString("CamPos : " + CamPos.ToString());

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Right");
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Left");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Down");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Up");
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsUp('D'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}
	if (true == UEngineInput::GetInst().IsUp('A'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Left");
	}
	if (true == UEngineInput::GetInst().IsUp('W'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Up");
	}
	if (true == UEngineInput::GetInst().IsUp('S'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Down");
	}

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