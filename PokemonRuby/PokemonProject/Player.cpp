#include "PreCompile.h"
#include "Player.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineInput.h>


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonMapMode.h"
#include "PokemonEnum.h"
#include "PokemonInput.h"
#include "EventTarget.h"


//

APlayer::APlayer()
{

    {
        SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

        SpriteRenderer->SetSprite("Player_Walk_Up.png");
        SpriteRenderer->SetSprite("Player_Walk_Down.png");
        SpriteRenderer->SetSprite("Player_Walk_Right.png");
        SpriteRenderer->SetSprite("Player_Walk_Left.png");

        SpriteRenderer->SetComponentScale({ 300, 300 });

        SpriteRenderer->CreateAnimation("Walk_Up", "Player_Walk_Up.png", 0, 4, 0.24f);
        SpriteRenderer->CreateAnimation("Walk_Down", "Player_Walk_Down.png", 0, 4, 0.24f);
        SpriteRenderer->CreateAnimation("Walk_Right", "Player_Walk_Right.png", 0, 4, 0.24f);
        SpriteRenderer->CreateAnimation("Walk_Left", "Player_Walk_Left.png", 0, 4, 0.24f);



        SpriteRenderer->CreateAnimation("Idle_Up", "Player_Walk_Up.png", 0, 0, 0.3f);
        SpriteRenderer->CreateAnimation("Idle_Down", "Player_Walk_Down.png", 0, 0, 0.3f);
        SpriteRenderer->CreateAnimation("Idle_Left", "Player_Walk_Left.png", 0, 0, 0.3f);
        SpriteRenderer->CreateAnimation("Idle_Right", "Player_Walk_Right.png", 0, 0, 0.3f);

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

//
//void APlayer::Tick(float _DeltaTime)
//{
//    Super::Tick(_DeltaTime);
//
//    // 이동 중일 때
//    if (bIsMoving)
//    {
//        FVector2D TargetLocation = GetTargetLocation();
//        FVector2D CurrentLocation = GetActorLocation();
//
//        // Lerp로 부드럽게 이동
//        FVector2D NewLocation = UPokemonMath::Lerp(CurrentLocation, TargetLocation, WalkSpeed * _DeltaTime);
//
//        // 목표에 가까워지면 위치를 정확히 설정하고 이동 종료
//        if ((NewLocation - TargetLocation).Length() < 1.0f)
//        {
//            NewLocation = TargetLocation;
//            bIsMoving = false; // 이동 종료
//        }
//
//        SetActorLocation(NewLocation);
//    }
//
//    FSM.Update(_DeltaTime);
//}
void APlayer::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    // 이동 중일 때
    if (bIsMoving)
    {
        FVector2D TargetLocation = GetTargetLocation();
        FVector2D CurrentLocation = GetActorLocation();

        // Lerp로 부드럽게 이동 (1초에 한 타일 이동)
        FVector2D NewLocation = UPokemonMath::Lerp(CurrentLocation, TargetLocation, _DeltaTime);

        // 목표에 가까워지면 위치를 정확히 설정하고 이동 종료
        if ((NewLocation - TargetLocation).Length() < 1.0f)
        {
            NewLocation = TargetLocation;
            bIsMoving = false; // 이동 종료
        }

        SetActorLocation(NewLocation);
    }

    FSM.Update(_DeltaTime);
}


//
//void APlayer::Idle(float _DeltaTime)
//{
//    PlayerCameraCheck();
//    PlayerDebugCheck(_DeltaTime);
//
//    // 버튼을 눌렀을 때 이동 시작
//    if (true == UEngineInput::GetInst().IsPress('W') && !bIsMoving)
//    {
//        CurDir = EPlayerDir::UP;
//        FVector2D CurrentLocation = GetActorLocation();
//        SetTargetLocation(CurrentLocation + FVector2D(0, -96));  // 위로 한 타일
//        bIsMoving = true;
//        FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
//        return;
//    }
//    if (true == UEngineInput::GetInst().IsPress('A') && !bIsMoving)
//    {
//        CurDir = EPlayerDir::LEFT;
//        FVector2D CurrentLocation = GetActorLocation();
//        SetTargetLocation(CurrentLocation + FVector2D(-96, 0));  // 왼쪽으로 한 타일
//        bIsMoving = true;
//        FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
//        return;
//    }
//    if (true == UEngineInput::GetInst().IsPress('S') && !bIsMoving)
//    {
//        CurDir = EPlayerDir::DOWN;
//        FVector2D CurrentLocation = GetActorLocation();
//        SetTargetLocation(CurrentLocation + FVector2D(0, 96));  // 아래로 한 타일
//        bIsMoving = true;
//        FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
//        return;
//    }
//    if (true == UEngineInput::GetInst().IsPress('D') && !bIsMoving)
//    {
//        CurDir = EPlayerDir::RIGHT;
//        FVector2D CurrentLocation = GetActorLocation();
//        SetTargetLocation(CurrentLocation + FVector2D(96, 0));  // 오른쪽으로 한 타일
//        bIsMoving = true;
//        FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
//        return;
//    }
//}
void APlayer::Idle(float _DeltaTime)
{
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);

    // 이동을 시작할 때
    if (!bIsMoving)
    {
        FVector2D CurrentLocation = GetActorLocation();

        if (UEngineInput::GetInst().IsPress('W'))
        {
            CurDir = EPlayerDir::UP;
            SetTargetLocation(CurrentLocation + FVector2D(0, -96));  // 위로 한 타일
            bIsMoving = true;
            FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
        }
        else if (UEngineInput::GetInst().IsPress('A'))
        {
            CurDir = EPlayerDir::LEFT;
            SetTargetLocation(CurrentLocation + FVector2D(-96, 0));  // 왼쪽으로 한 타일
            bIsMoving = true;
            FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
        }
        else if (UEngineInput::GetInst().IsPress('S'))
        {
            CurDir = EPlayerDir::DOWN;
            SetTargetLocation(CurrentLocation + FVector2D(0, 96));  // 아래로 한 타일
            bIsMoving = true;
            FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
        }
        else if (UEngineInput::GetInst().IsPress('D'))
        {
            CurDir = EPlayerDir::RIGHT;
            SetTargetLocation(CurrentLocation + FVector2D(96, 0));  // 오른쪽으로 한 타일
            bIsMoving = true;
            FSM.ChangeState(APlayerState::WALK);  // 이동 상태로 변경
        }
    }
}




void APlayer::Walk(float _DeltaTime)
{
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);

    FVector2D MoveDirection = FVector2D::ZERO;
    FVector2D TargetLocation = GetActorLocation();

    if (true == UEngineInput::GetInst().IsPress('D'))
    {
        MoveDirection += FVector2D::RIGHT;
        TargetLocation.X += 96;  // 오른쪽으로 한 타일 이동
        CurDir = EPlayerDir::RIGHT;
    }
    if (true == UEngineInput::GetInst().IsPress('A'))
    {
        MoveDirection += FVector2D::LEFT;
        TargetLocation.X -= 96;  // 왼쪽으로 한 타일 이동
        CurDir = EPlayerDir::LEFT;
    }
    if (true == UEngineInput::GetInst().IsPress('S'))
    {
        MoveDirection += FVector2D::DOWN;
        TargetLocation.Y += 96;  // 아래로 한 타일 이동
        CurDir = EPlayerDir::DOWN;
    }
    if (true == UEngineInput::GetInst().IsPress('W'))
    {
        MoveDirection += FVector2D::UP;
        TargetLocation.Y -= 96;  // 위로 한 타일 이동
        CurDir = EPlayerDir::UP;
    }

    SetTargetLocation(TargetLocation);
    bIsMoving = true;

    // 이동 완료 시 상태 변경
    if (true == UEngineInput::GetInst().IsUp('W') || true == UEngineInput::GetInst().IsUp('A') ||
        true == UEngineInput::GetInst().IsUp('S') || true == UEngineInput::GetInst().IsUp('D'))
    {
        ChangeState(APlayerState::IDLE);
        FSM.ChangeState(APlayerState::IDLE);
        bIsMoving = false;
    }
}



void APlayer::ChangeState(APlayerState _CurPlayerState)
{
    switch (_CurPlayerState)
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

    CurPlayerState = _CurPlayerState;

}

void APlayer::IdleStart()
{
    if (true == UEngineInput::GetInst().IsUp('D'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Right");
        return;
    }
    if (true == UEngineInput::GetInst().IsUp('A'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Left");
        return;
    }
    if (true == UEngineInput::GetInst().IsUp('S'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Down");
        return;
    }
    if (true == UEngineInput::GetInst().IsUp('W'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Up");
        return;
    }

    
    
}


void APlayer::WalkStart()
{
    if (CurDir == EPlayerDir::RIGHT)
    {
        SpriteRenderer->ChangeAnimation("Walk_Right");
    }
    else if (CurDir == EPlayerDir::LEFT)
    {
        SpriteRenderer->ChangeAnimation("Walk_Left");
    }
    else if (CurDir == EPlayerDir::DOWN)
    {
        SpriteRenderer->ChangeAnimation("Walk_Down");
    }
    else if (CurDir == EPlayerDir::UP)
    {
        SpriteRenderer->ChangeAnimation("Walk_Up");
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



void APlayer::PlayerCameraCheck()
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    GetWorld()->SetCameraPos(GetActorLocation() - Size.Half());
    MapSizeCheck(Size);
  
}

void APlayer::MapSizeCheck(FVector2D _Size)
{
   
    FVector2D MapEnd = MapSize - _Size;
    FVector2D CamPos = GetWorld()->GetCameraPos();
    FVector2D ActorLocation = GetActorLocation();

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
        CamPos.X = MapSize.Half().X - _Size.Half().X;
    }
    if (0 >= CamPos.Y)
    {
        CamPos.Y = 0.0f;
    }
    if (MapEnd.Y <= CamPos.Y)
    {
        CamPos.Y = MapEnd.Y;
    }
    if (0 >= MapEnd.Y)
    {
        CamPos.Y = MapSize.Half().Y - _Size.Half().Y;
    }

    if (ActorLocation.X < 0)
    {
        ActorLocation.X = 0;
    }
    if (ActorLocation.X > MapSize.X)
    {
        ActorLocation.X = MapSize.X;
    }

    if (ActorLocation.Y < 0)
    {
        ActorLocation.Y = 0;
    }
    if (ActorLocation.Y > MapSize.Y)
    {
        ActorLocation.Y = MapSize.Y;
    }

    SetActorLocation(ActorLocation);

    GetWorld()->SetCameraPos(CamPos);
}

void APlayer::PlayerDebugCheck(float _DeltaTime)
{
    FVector2D CamPos = GetWorld()->GetCameraPos();
    UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
    UEngineDebug::CoreOutPutString("PlayerPos : " + std::to_string(GetActorLocation().iX() / 96) + ", " + std::to_string(GetActorLocation().iY() / 96));
    UEngineDebug::CoreOutPutString("CamPos : " + CamPos.ToString());


    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    FVector2D NewCameraPos = GetActorLocation() - Size.Half();

    // 카메라 위치를 부드럽게 이동
    GetWorld()->SetCameraPos(UPokemonMath::Lerp(GetWorld()->GetCameraPos(), NewCameraPos, WalkSpeed * 0.5f));
    MapSizeCheck(Size);

}



void APlayer::SetObject()
{
    PlayerCameraCheck();
    GetWorld()->SetCameraToMainPawn(false);
    SpriteRenderer->SetOrder(ERenderOrder::PLAYER);

    AGameMode* Curmode = UEngineAPICore::GetCore()->GetCurLevel()->GetGameMode();
    SpriteMapRenderer = Curmode->Map;
    MapSize = SpriteMapRenderer->GetComponentScale();
    SpriteRenderer->SetComponentLocation({ 48, 24 });
    FTileVector startPos = { 92, 70 };
    SetActorLocation(startPos.ToFVector());
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




// 목표 위치 설정 함수
void APlayer::SetTargetLocation(const FVector2D& NewTarget)
{
    TargetLocation = NewTarget;
}

// 목표 위치 반환 함수
FVector2D APlayer::GetTargetLocation() const
{
    return TargetLocation;
}