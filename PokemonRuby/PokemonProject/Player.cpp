#include "PreCompile.h"
#include "Player.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineRandom.h>

#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWInImage.h>


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>


#include "PokemonEnum.h"
#include "PokemonInput.h"
#include "WildPokemon.h"




APlayer::APlayer()
{

    {
        SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

        SpriteRenderer->SetSprite("Player_Walk_Up.png");
        SpriteRenderer->SetSprite("Player_Walk_Down.png");
        SpriteRenderer->SetSprite("Player_Walk_Right.png");
        SpriteRenderer->SetSprite("Player_Walk_Left.png");

        SpriteRenderer->SetComponentScale({ 300, 300 });

        SpriteRenderer->CreateAnimation("Walk_Up", "Player_Walk_Up.png", 1, 3, 0.2f);
        SpriteRenderer->CreateAnimation("Walk_Down", "Player_Walk_Down.png", 1, 3, 0.2f);
        SpriteRenderer->CreateAnimation("Walk_Right", "Player_Walk_Right.png", 1, 3, 0.2f);
        SpriteRenderer->CreateAnimation("Walk_Left", "Player_Walk_Left.png", 1, 3, 0.2f);



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

void APlayer::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
    
    if (true == IsMoving)
    {
        WalkTime += _DeltaTime;

        if (WalkTime >= TileMoveTime)
        {
            SetActorLocation(TargetLocation);
            IsMoving = false;
            WalkTime = 0.0f;
            FSM.ChangeState(APlayerState::IDLE);
        }
        else
        {
            FVector2D NewLocation = UPokemonMath::Lerp(GetActorLocation(), TargetLocation, WalkTime / TileMoveTime);
            SetActorLocation(NewLocation);
        }
    }

    FSM.Update(_DeltaTime);
}


void APlayer::Idle(float _DeltaTime)
{
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);
    

    if (true == IsMoving)
    {
        return;
    }

    if (UEngineInput::GetInst().IsPress('W') && true != IsMoving)
    {
        CurDir = EPlayerDir::UP;
        FVector2D CurrentLocation = GetActorLocation();
        SetTargetLocation(CurrentLocation + FVector2D(0.0f, -TileSize.Y));
        FSM.ChangeState(APlayerState::WALK);
        return;
    }
    if (UEngineInput::GetInst().IsPress('A') && true != IsMoving)
    {
        CurDir = EPlayerDir::LEFT;
        FVector2D CurrentLocation = GetActorLocation();
        SetTargetLocation(CurrentLocation + FVector2D(-TileSize.X, 0.0f));
        FSM.ChangeState(APlayerState::WALK);
        return;
    }
    if (UEngineInput::GetInst().IsPress('S') && true != IsMoving)
    {
        CurDir = EPlayerDir::DOWN;
        FVector2D CurrentLocation = GetActorLocation();
        SetTargetLocation(CurrentLocation + FVector2D(0.0f, TileSize.Y));
        FSM.ChangeState(APlayerState::WALK);
        return;
    }
    if (UEngineInput::GetInst().IsPress('D') && true != IsMoving)
    {
        CurDir = EPlayerDir::RIGHT;
        FVector2D CurrentLocation = GetActorLocation();
        SetTargetLocation(CurrentLocation + FVector2D(TileSize.X, 0.0f));
        FSM.ChangeState(APlayerState::WALK);
        return;
    }

    if (UEngineInput::GetInst().IsPress('W') || UEngineInput::GetInst().IsPress('A') ||
        UEngineInput::GetInst().IsPress('S') || UEngineInput::GetInst().IsPress('D'))
    {
        SpriteRenderer->ChangeAnimation("Walk" + DirString[static_cast<int>(CurDir)]);
    }
    else
    {
        SpriteRenderer->ChangeAnimation("Idle" + DirString[static_cast<int>(CurDir)]);
    }
}

void APlayer::Walk(float _DeltaTime)
{
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);

    FVector2D CurrentLocation = GetActorLocation();
    FVector2D TargetLocation = GetTargetLocation();

    if (false == IsMoving)
    {
        TargetLocation = CurrentLocation;
    }
    
    PlayerGroundCheck(TargetLocation);
    
    FVector2D Direction = TargetLocation - CurrentLocation;
    Direction.Normalize();

    FVector2D NewLocation = UPokemonMath::Lerp(CurrentLocation, TargetLocation, WalkSpeed * _DeltaTime);
    UEngineRandom Encounter;
    int EncounterInt= Encounter.RandomInt( 0 , 9 );


    if ((NewLocation - TargetLocation).Length() < 0.1f)
    {
        NewLocation = TargetLocation;
        IsMoving = false;

        if (UColor::GREEN == CheckColor && 2 > EncounterInt)
        {
            UEngineAPICore::GetCore()->OpenLevel("PokemonBattle");
        }

        FSM.ChangeState(APlayerState::IDLE);
    }

    SetActorLocation(NewLocation);

    if (UEngineInput::GetInst().IsPress('W') || UEngineInput::GetInst().IsPress('A') ||
        UEngineInput::GetInst().IsPress('S') || UEngineInput::GetInst().IsPress('D'))
    {
        SpriteRenderer->ChangeAnimation("Walk" + DirString[static_cast<int>(CurDir)]);
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
    if (CurDir == EPlayerDir::RIGHT)
    {
        SpriteRenderer->ChangeAnimation("Idle_Right");
    }
    else if (CurDir == EPlayerDir::LEFT)
    {
        SpriteRenderer->ChangeAnimation("Idle_Left");
    }
    else if (CurDir == EPlayerDir::DOWN)
    {
        SpriteRenderer->ChangeAnimation("Idle_Down");
    }
    else if (CurDir == EPlayerDir::UP)
    {
        SpriteRenderer->ChangeAnimation("Idle_Up");
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



void APlayer::SetTargetLocation(const FVector2D& NewTarget)
{
    FVector2D Target = FVector2D
    (
        std::round(NewTarget.X / TileSize.X) * TileSize.X,
        std::round(NewTarget.Y / TileSize.Y) * TileSize.Y
    );

    TargetLocation = Target;
    IsMoving = true;
    WalkTime = 0.0f;
    PlayerGroundCheck(TargetLocation);

    if (CheckColor == UColor::WHITE)
    {
        IsMoving = true;
    }
    if (CheckColor == UColor::RED)
    {
        IsMoving = false;
        TargetLocation == GetActorLocation();
    }

    CurrentDirection = TargetLocation - GetActorLocation();
    CurrentDirection.Normalize();
}

FVector2D APlayer::GetTargetLocation() const
{
    return TargetLocation;
}

void APlayer::PlayerGroundCheck(FVector2D _MovePos)
{
    if (nullptr != ColImage)
    {
        FVector2D NextPos = _MovePos;
        CheckColor = ColImage->GetColor(NextPos);
    }
}

void APlayer::SetColImage(std::string_view _ColImageName)
{
    ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}
