#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonMapMode.h"
#include "PokemonEnum.h"
#include "PokemonInput.h"





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
}


void APlayer::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);
    StateUpdate(_DeltaTime);


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
    case APlayerState::NONE:
        StateChange(APlayerState::IDLE);
        break;
    case APlayerState::IDLE:
        Idle(_DeltaTime);
        break;
    case APlayerState::WALK:
        Walk(_DeltaTime);
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
    case APlayerState::IDLE:
        IdleStart();
        break;
    case APlayerState::WALK:
        WalkStart();
        break;
    default:
        break;
    }

    CurPlayerState = _State;
}

void APlayer::ChangeAnimation(APlayerState _State, FTileVector _Direction)
{
    switch (_State)
    {
    case APlayerState::IDLE:
        SpriteRenderer->ChangeAnimation("Idle_" + _Direction.ToDirectionString());
        break;
    case APlayerState::WALK:
        SpriteRenderer->ChangeAnimation("Walk_" + _Direction.ToDirectionString());
        break;

    default:
        break;
    }

}

void APlayer::Idle(float _DeltaTime)
{
    FTileVector KeyPressDirection = UPokemonInput::GetPressDirection();

    if (KeyPressDirection == Direction)
    {
        StateChange(APlayerState::WALK);
        return;
    }

    if (KeyPressDirection == FTileVector::Zero)
    {
        return;
    }

    if (KeyPressDirection != Direction)
    {
        IsRotate = true;
        Direction = KeyPressDirection;
        CurRotateTime = RotateTime;
        ChangeAnimation(APlayerState::WALK, Direction);
        return;
    }

}

void APlayer::Walk(float _DeltaTime)
{
    if (CurWalkTime > 0.0f)
    {
        IsExecutingMovingLogic = true;

        CurWalkTime -= _DeltaTime;

        float t = (WalkTime - CurWalkTime) / WalkTime;

        FTileVector TargetPos = UPokemonMath::Lerp(CurPos, NextPos, t);
        SetActorTileLocation(TargetPos);
        FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
        GetWorld()->SetCameraPos(GetActorLocation() - Size.Half());

        if (t >= WalkInputLatency)
        {
            PrevPos = UPokemonInput::GetPressDirection();
        }

        return;
    }
    IsExecutingMovingLogic = false;

    WalkStart();
}

void APlayer::IdleStart()
{
    ChangeAnimation(APlayerState::IDLE, Direction);
}

void APlayer::WalkStart()
{
    ChangeAnimation(APlayerState::WALK, Direction);
}


FTileVector APlayer::SetActorTileLocation(FTileVector _CurPos)
{
    return   _CurPos.ToFVector();
}