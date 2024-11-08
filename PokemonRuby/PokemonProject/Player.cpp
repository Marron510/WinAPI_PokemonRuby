#include "PreCompile.h"
#include "Player.h"

#include <EngineBase/EngineMath.h>
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

std::string DirString[static_cast<int>(APlayer::EPlayerDir::MAX)] =
{
    "_Left",
    "_Right",
    "_Up",
    "_Down"
};


void APlayer::BeginPlay()
{
    Super::BeginPlay();
    SetObject();

    FSM.CreateState(APlayer::APlayerState::IDLE, std::bind(&APlayer::Idle, this, std::placeholders::_1),
        [this]()
        {
            SpriteRenderer->ChangeAnimation("Idle" + DirString[static_cast<int>(CurDir)]);
        }
    );

    FSM.CreateState(APlayer::APlayerState::WALK, std::bind(&APlayer::Walk, this, std::placeholders::_1),
        [this]()
        {
            SpriteRenderer->ChangeAnimation("Walk" + DirString[static_cast<int>(CurDir)]);        
        }
    );

    FSM.ChangeState(APlayerState::IDLE);

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
    switch (State)
    {
    case APlayerState::NONE:
        StateChange(APlayer::APlayerState::IDLE);
        FSM.Update(_DeltaTime);
        break;
    case APlayerState::IDLE:
        Idle(_DeltaTime);
        FSM.Update(_DeltaTime);
        break;
    case APlayerState::WALK:
        
        Walk(_DeltaTime);
        FSM.Update(_DeltaTime);
        break;

    default:
        break;
    }
}
void APlayer::StateChange(APlayer::APlayerState _State)
{
    switch (_State)
    {
    case APlayer::APlayerState::NONE:

        break;
    case APlayer::APlayerState::IDLE:

        IdleStart();

        break;
    case APlayer::APlayerState::WALK:

        WalkStart();

        break;
        
    }
}

void APlayer::Walk(float _DeltaTime)
{
    PlayerCameraCheck();

    FVector2D Vector = FVector2D::ZERO;

    if (true == UEngineInput::GetInst().IsPress('D'))
    {
        CurDir = EPlayerDir::RIGHT;
        FSM.ChangeState(APlayerState::WALK);
        Vector += FVector2D::RIGHT;
    }
    if (true == UEngineInput::GetInst().IsPress('A'))
    {
        CurDir = EPlayerDir::LEFT;
        FSM.ChangeState(APlayerState::WALK);
        Vector += FVector2D::LEFT;
    }
    if (true == UEngineInput::GetInst().IsPress('S'))
    {
        CurDir = EPlayerDir::DOWN;
        FSM.ChangeState(APlayerState::WALK);
        Vector += FVector2D::DOWN;
    }
    if (true == UEngineInput::GetInst().IsPress('W'))
    {
        CurDir = EPlayerDir::UP;
        FSM.ChangeState(APlayerState::WALK);
        Vector += FVector2D::UP;
    }

      AddActorLocation(Vector * _DeltaTime * WalkSpeed);
    


    if (false == UEngineInput::GetInst().IsPress('A') &&
        false == UEngineInput::GetInst().IsPress('D') &&
        false == UEngineInput::GetInst().IsPress('W') &&
        false == UEngineInput::GetInst().IsPress('S'))
    {
        FSM.ChangeState(APlayerState::IDLE);
        return;
    }

    

}


void APlayer::Idle(float _DeltaTime)
{
    PlayerCameraCheck();

     APlayer::EPlayerDir CurKeyDir = APlayer::GetPressDirection();

     if (CurDir == CurKeyDir)
     {
         StateChange(APlayerState::WALK);
     }
     else if (CurDir != CurKeyDir)
     {
         CurDir = CurKeyDir;
         StateChange(APlayerState::WALK);
     }
}




void APlayer::SetObject()
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
    GetWorld()->SetCameraToMainPawn(false);
    SpriteRenderer->SetOrder(ERenderOrder::PLAYER);
    AGameMode* Curmode = UEngineAPICore::GetCore()->GetCurLevel()->GetGameMode();
    SpriteMapRenderer = Curmode->Map;
    MapSize = SpriteMapRenderer->GetComponentScale();
    CurPos = { MapSize.Half().X, MapSize.Half().Y };
    SetActorLocation(CurPos);
    State = APlayerState::NONE;
}


void APlayer::IdleStart()
{
    if (true == UEngineInput::GetInst().IsDown('W'))
    {
        SpriteRenderer->ChangeAnimation("IDLE_UP");
        FSM.ChangeState(APlayerState::WALK);
        return;
    }
    else if (true == UEngineInput::GetInst().IsDown('A'))
    {
        SpriteRenderer->ChangeAnimation("IDLE_LEFT");
        FSM.ChangeState(APlayerState::WALK);
        return;
    }
    else if (true == UEngineInput::GetInst().IsDown('S'))
    {
        SpriteRenderer->ChangeAnimation("IDLE_DOWN");
        FSM.ChangeState(APlayerState::WALK);
        return;
    }
    else if (true == UEngineInput::GetInst().IsDown('D'))
    {
        SpriteRenderer->ChangeAnimation("IDLE_RIGHT");
        FSM.ChangeState(APlayerState::WALK);
        return;
    }
}

void APlayer::WalkStart()
{
    if (true == UEngineInput::GetInst().IsUp('W'))
    {
        SpriteRenderer->ChangeAnimation("Walk_Up");
        return;
    }
    else if (true == UEngineInput::GetInst().IsUp('A'))
    {
        SpriteRenderer->ChangeAnimation("Walk_Left");
        return;
    }
    else if (true == UEngineInput::GetInst().IsUp('S'))
    {
        SpriteRenderer->ChangeAnimation("WALK_Down");
        return;
    }
    else if (true == UEngineInput::GetInst().IsUp('D'))
    {
        SpriteRenderer->ChangeAnimation("Walk_Right");

    }
}

void APlayer::CreatePlayerDirState(APlayer::EPlayerDir _Dir)
{
    FSM.CreateState(APlayer::APlayerState::IDLE, std::bind(&APlayer::Idle, this, std::placeholders::_1),
        [this]()
        {
            SpriteRenderer->ChangeAnimation("Idle_Right");
        }
    );
}


APlayer::EPlayerDir APlayer::GetPressDirection()
{
    APlayer::EPlayerDir NextDirection = CurDir;

    if (UEngineInput::GetInst().IsPress('S'))
    {
        NextDirection = APlayer::EPlayerDir::DOWN;
    }
    else if (UEngineInput::GetInst().IsPress('W'))
    {
        NextDirection = APlayer::EPlayerDir::UP;
    }
    else if (UEngineInput::GetInst().IsPress('A'))
    {
        NextDirection = APlayer::EPlayerDir::LEFT;
    }
    else if (UEngineInput::GetInst().IsPress('D'))
    {
        NextDirection = APlayer::EPlayerDir::RIGHT;
    }

    return NextDirection;
}
