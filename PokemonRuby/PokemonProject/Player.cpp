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
    SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
    SpriteRenderer->SetComponentScale({ 300, 300 });

    InitializeSprites();
    InitializeAnimations();
}

APlayer::~APlayer()
{
}

std::string DirString[static_cast<int>(APlayer::EPlayerDir::MAX)] =
{
    "_Left_Left_Arm",
    "_Left_Right_Arm",
    "_Right_Left_Arm",
    "_Right_Right_Arm",
    "_Up_Left_Arm",
    "_Up_Right_Arm",
    "_Down_Left_Arm",
    "_Down_Right_Arm"
};


void APlayer::BeginPlay()
{
    Super::BeginPlay();
    SetObject();

    FSM.CreateState(APlayer::APlayerState::IDLE,
        std::bind(&APlayer::Idle, this, std::placeholders::_1),
        [this]() { SpriteRenderer->ChangeAnimation("Idle" + DirString[static_cast<int>(CurDir)]); }
    );

    FSM.CreateState(APlayer::APlayerState::WALK,
        std::bind(&APlayer::Walk, this, std::placeholders::_1),
        [this]() { SpriteRenderer->ChangeAnimation("Walk" + DirString[static_cast<int>(CurDir)]); }
    );

    FSM.ChangeState(APlayerState::IDLE);
}


void APlayer::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    if (IsMoving)
    {
        UpdateMovement(_DeltaTime);
    }

    FSM.Update(_DeltaTime);
}

void APlayer::Idle(float _DeltaTime)
{
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);

    if (IsMoving) return;

    HandleInput();
}

void APlayer::Walk(float _DeltaTime)
{
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);

    // 이동 완료 여부 확인
    if (!IsMoving)
    {
        FSM.ChangeState(APlayerState::IDLE); // IDLE 상태로 전환
    }
    else
    {
        WalkTime += _DeltaTime;

        if (WalkTime >= TileMoveTime / 2.0f)
        {
            ChangeArmAnimation();
            WalkTime = 0.0f; // 애니메이션 변경 후 WalkTime 초기화
        }
    }
}



void APlayer::HandleInput()
{
    // 키 입력 확인 및 처리
    if (UEngineInput::GetInst().IsPress('W'))
    {
        StartMovement(EPlayerDir::UP_Left_Arm, { 0.0f, -TileSize.Y });
    }
    else if (UEngineInput::GetInst().IsPress('A'))
    {
        StartMovement(EPlayerDir::LEFT_Left_Arm, { -TileSize.X, 0.0f });
    }
    else if (UEngineInput::GetInst().IsPress('S'))
    {
        StartMovement(EPlayerDir::DOWN_Left_Arm, { 0.0f, TileSize.Y });
    }
    else if (UEngineInput::GetInst().IsPress('D'))
    {
        StartMovement(EPlayerDir::RIGHT_Left_Arm, { TileSize.X, 0.0f });
    }
    else
    {
        IsMoving = false;
        bIsLeftArm = true;
        FSM.ChangeState(APlayerState::IDLE);
    }
}



void APlayer::StartMovement(EPlayerDir Direction, FVector2D Offset)
{
    CurDir = Direction;
    SetTargetLocation(GetActorLocation() + Offset);
    FSM.ChangeState(APlayerState::WALK);
}

void APlayer::UpdateMovement(float _DeltaTime)
{
    WalkTime += _DeltaTime;

    // 현재 위치와 목표 위치의 차이를 계산
    FVector2D CurrentLocation = GetActorLocation();
    if ((TargetLocation - CurrentLocation).Length() < 0.1f)
    {
        // 이동 완료
        SetActorLocation(TargetLocation); // 최종 위치 설정
        IsMoving = false;
        WalkTime = 0.0f;
        FSM.ChangeState(APlayerState::IDLE); // IDLE 상태로 전환
    }
    else
    {
        // Lerp를 사용한 부드러운 이동 처리
        FVector2D NewLocation = UPokemonMath::Lerp(CurrentLocation, TargetLocation, WalkTime / TileMoveTime);
        SetActorLocation(NewLocation);

        // 타일 한 칸 이동 중간 시점마다 애니메이션 변경
        if (WalkTime >= TileMoveTime / 2.0f)
        {
            ChangeArmAnimation(); // 왼손/오른손 애니메이션 전환
            WalkTime = 0.0f; // 다음 타일 이동을 위해 초기화
        }
    }
}




void APlayer::HandleBattleEncounter()
{
    UEngineRandom Encounter;
    int EncounterInt = Encounter.RandomInt(0, 9);

    if (CheckColor == UColor::GREEN && EncounterInt < 2)
    {
        UEngineAPICore::GetCore()->OpenLevel("PokemonBattle");
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
        break;
    default:
        break;
    }

    CurPlayerState = _CurPlayerState;

}


void APlayer::IdleStart()
{
    if (CurDir == EPlayerDir::RIGHT_Left_Arm)
    {
        SpriteRenderer->ChangeAnimation("Idle_Right");
    }
    else if (CurDir == EPlayerDir::LEFT_Left_Arm)
    {
        SpriteRenderer->ChangeAnimation("Idle_Left");
    }
    else if (CurDir == EPlayerDir::DOWN_Left_Arm)
    {
        SpriteRenderer->ChangeAnimation("Idle_Down");
    }
    else if (CurDir == EPlayerDir::UP_Left_Arm)
    {
        SpriteRenderer->ChangeAnimation("Idle_Up");
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
void APlayer::ChangeArmAnimation()
{
    std::string AnimationName;

    switch (CurDir)
    {
    case EPlayerDir::RIGHT_Left_Arm:
        AnimationName = bIsLeftArm ? "Walk_Right_Left_Arm" : "Walk_Right_Right_Arm";
        break;
    case EPlayerDir::LEFT_Left_Arm:
        AnimationName = bIsLeftArm ? "Walk_Left_Left_Arm" : "Walk_Left_Right_Arm";
        break;
    case EPlayerDir::DOWN_Left_Arm:
        AnimationName = bIsLeftArm ? "Walk_Down_Left_Arm" : "Walk_Down_Right_Arm";
        break;
    case EPlayerDir::UP_Left_Arm:
        AnimationName = bIsLeftArm ? "Walk_Up_Left_Arm" : "Walk_Up_Right_Arm";
        break;
    default:
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
    bIsLeftArm = !bIsLeftArm; // 왼팔과 오른팔 전환
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
        NextDirection = APlayer::EPlayerDir::DOWN_Left_Arm;
    }
    else if (UEngineInput::GetInst().IsPress('W'))
    {
        NextDirection = APlayer::EPlayerDir::UP_Left_Arm;
    }
    else if (UEngineInput::GetInst().IsPress('A'))
    {
        NextDirection = APlayer::EPlayerDir::LEFT_Left_Arm;
    }
    else if (UEngineInput::GetInst().IsPress('D'))
    {
        NextDirection = APlayer::EPlayerDir::RIGHT_Left_Arm;
    }

    return NextDirection;
}



void APlayer::SetTargetLocation(const FVector2D& NewTarget)
{
    FVector2D Target = FVector2D(
        std::round(NewTarget.X / TileSize.X) * TileSize.X,
        std::round(NewTarget.Y / TileSize.Y) * TileSize.Y
    );

    TargetLocation = Target;
    IsMoving = true; // 이동 플래그 설정
    WalkTime = 0.0f; // WalkTime 초기화

    PlayerGroundCheck(TargetLocation);
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


void APlayer::InitializeSprites()
{
    SpriteRenderer->SetSprite("Player_Walk_Up.png");
    SpriteRenderer->SetSprite("Player_Walk_Down.png");
    SpriteRenderer->SetSprite("Player_Walk_Right.png");
    SpriteRenderer->SetSprite("Player_Walk_Left.png");
}


void APlayer::InitializeAnimations()
{
    float FrameTime = TileMoveTime / 1.0f; 

    SpriteRenderer->CreateAnimation("Walk_Up_Left_Arm", "Player_Walk_Up.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Up_Right_Arm", "Player_Walk_Up.png", 3, 4, FrameTime);

    SpriteRenderer->CreateAnimation("Walk_Down_Left_Arm", "Player_Walk_Down.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Down_Right_Arm", "Player_Walk_Down.png", 3, 4, FrameTime);

    SpriteRenderer->CreateAnimation("Walk_Right_Left_Arm", "Player_Walk_Right.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Right_Right_Arm", "Player_Walk_Right.png", 3, 4, FrameTime);

    SpriteRenderer->CreateAnimation("Walk_Left_Left_Arm", "Player_Walk_Left.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Left_Right_Arm", "Player_Walk_Left.png", 3, 4, FrameTime);

    float IdleFrameTime = 0.2f;
    SpriteRenderer->CreateAnimation("Idle_Up_Left_Arm", "Player_Walk_Up.png", 0, 0, IdleFrameTime);
    SpriteRenderer->CreateAnimation("Idle_Up_Right_Arm", "Player_Walk_Up.png", 0, 0, IdleFrameTime);

    SpriteRenderer->CreateAnimation("Idle_Down_Left_Arm", "Player_Walk_Down.png", 0, 0, IdleFrameTime);
    SpriteRenderer->CreateAnimation("Idle_Down_Right_Arm", "Player_Walk_Down.png", 0, 0, IdleFrameTime);

    SpriteRenderer->CreateAnimation("Idle_Left_Left_Arm", "Player_Walk_Left.png", 0, 0, IdleFrameTime);
    SpriteRenderer->CreateAnimation("Idle_Left_Right_Arm", "Player_Walk_Left.png", 0, 0, IdleFrameTime);

    SpriteRenderer->CreateAnimation("Idle_Right_Left_Arm", "Player_Walk_Right.png", 0, 0, IdleFrameTime);
    SpriteRenderer->CreateAnimation("Idle_Right_Right_Arm", "Player_Walk_Right.png", 0, 0, IdleFrameTime);
}
