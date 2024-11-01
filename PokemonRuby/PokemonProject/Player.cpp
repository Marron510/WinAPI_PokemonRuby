#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>




void APlayer::RunSoundPlay()
{
	UEngineDebug::OutPutString("SoundPlay");
}
APlayer::APlayer()
{
	SetActorLocation({ 100, 100 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		
		SpriteRenderer->SetSprite("Player_Walk_Up.png");
		SpriteRenderer->SetSprite("Player_Walk_Down.png");
		SpriteRenderer->SetSprite("Player_Walk_Right.png");
		SpriteRenderer->SetSprite("Player_Walk_Left.png");
		SpriteRenderer->SetComponentScale({ 100, 100 });
		SpriteRenderer->SetComponentScale({ 100, 100 });
		SpriteRenderer->SetComponentScale({ 100, 100 });
		SpriteRenderer->SetComponentScale({ 100, 100 });
		SpriteRenderer->CreateAnimation("Walk_Up", "Player_Walk_Up.png", 0, 2, 0.1f);

		SpriteRenderer->CreateAnimation("Walk_Down", "Player_Walk_Down.png", 0, 2, 0.1f);

		SpriteRenderer->CreateAnimation("Walk_Right", "Player_Walk_Right.png", 0, 2, 0.1f);

		SpriteRenderer->CreateAnimation("Walk_Left", "Player_Walk_Left.png", 0, 2, 0.1f);





		SpriteRenderer->CreateAnimation("Idle_Up", "Player_Walk_Up.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Down", "Player_Walk_Down.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Left", "Player_Walk_Left.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Walk_Right.png", 0, 0, 0.1f);

		SpriteRenderer->ChangeAnimation("Idle_Down");

		SpriteRenderer->SetAnimationEvent("Walk_Down", 2, std::bind(&APlayer::RunSoundPlay, this));

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

}


void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}


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