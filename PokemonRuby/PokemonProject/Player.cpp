#include "PreCompile.h"
#include "Player.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineRandom.h>
#include <EngineBase/TimeEvent.h>

#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWInImage.h>


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>


#include "PokemonEnum.h"
#include "PokemonInput.h"
#include "WildPokemon.h"
#include "Fade.h"
#include "Mother.h"
#include "PokemonText.h"

APlayer::APlayer()
{
    SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

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


void APlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsJumping) 
    {
        UpdateJump(DeltaTime);
    }
    else if (IsMoving)
    {
        UpdateMovement(DeltaTime);
    }

    FSM.Update(DeltaTime);
}


void APlayer::Idle(float _DeltaTime)
{
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);

    if (IsMoving) return;

    HandleInput();
}

void APlayer::Walk(float _DeltaTime) {
    PlayerCameraCheck();
    PlayerDebugCheck(_DeltaTime);

    WalkTime += _DeltaTime;

    FVector2D CurrentLocation = GetActorLocation();

    if ((TargetLocation - CurrentLocation).Length() < 0.1f) {
        SetActorLocation(TargetLocation);
        IsMoving = false;
        FSM.ChangeState(APlayerState::IDLE);
        HandleBattleEncounter();
        return;
    }

    FVector2D NewLocation = UPokemonMath::Lerp(CurrentLocation, TargetLocation, WalkTime / TileMoveTime);
    SetActorLocation(NewLocation);

    if (WalkTime >= 0.4f) {
        ChangeArmAnimation();
        WalkTime -= 0.4f;
    }
}


void APlayer::HandleInput()
{
    if (!bCanMove || IsJumping)
    {
        FSM.ChangeState(APlayerState::IDLE);
        return;
    }

    if (UEngineInput::GetInst().IsPress('W'))
    {
        FVector2D NextPos = GetActorLocation() + FVector2D(0.0f, -TileSize.Y);
        UColor NextColor = ColImage->GetColor(NextPos);

        if (NextColor == UColor::RED || NextColor == UColor::BLUE)
        {
            IsMoving = false;
            BGMPlayer = UEngineSound::Play("SECollision.mp3");
            FSM.ChangeState(APlayerState::IDLE); 
            return;
        }

        StartMovementWithAnimation(EPlayerDir::UP_Left_Arm, EPlayerDir::UP_Right_Arm, { 0.0f, -TileSize.Y });
    }
    else if (UEngineInput::GetInst().IsPress('A'))
    {
        StartMovementWithAnimation(EPlayerDir::LEFT_Left_Arm, EPlayerDir::LEFT_Right_Arm, { -TileSize.X, 0.0f });
    }
    else if (UEngineInput::GetInst().IsPress('S'))
    {
        if (CheckColor == UColor::BLUE)
        {
            Jump();
        }
        else
        {
            StartMovementWithAnimation(EPlayerDir::DOWN_Left_Arm, EPlayerDir::DOWN_Right_Arm, { 0.0f, TileSize.Y });
        }
    }
    else if (UEngineInput::GetInst().IsPress('D'))
    {
        StartMovementWithAnimation(EPlayerDir::RIGHT_Left_Arm, EPlayerDir::RIGHT_Right_Arm, { TileSize.X, 0.0f });
    }
    else
    {
        IsMoving = false;
        FSM.ChangeState(APlayerState::IDLE);
    }
}




void APlayer::StartMovementWithAnimation(EPlayerDir LeftArmDir, EPlayerDir RightArmDir, FVector2D Offset) {
    DirectionMoveCount[LeftArmDir]++;
    bIsLeftArm = (DirectionMoveCount[LeftArmDir] % 2 != 0);
    CurDir = bIsLeftArm ? LeftArmDir : RightArmDir;

    SetTargetLocation(GetActorLocation() + Offset);
    IsMoving = true;
    FSM.ChangeState(APlayerState::WALK);
}


APlayer::EPlayerDir APlayer::GetArmDirection(EPlayerDir LeftArmDir, EPlayerDir RightArmDir)
{
    DirectionMoveCount[LeftArmDir]++;

    bool isLeftArm = (DirectionMoveCount[LeftArmDir] % 2 != 0);

    bIsLeftArm = isLeftArm;

    return isLeftArm ? LeftArmDir : RightArmDir;
}


void APlayer::StartMovement(EPlayerDir Direction, FVector2D Offset) {
    CurDir = Direction;

    MoveCount++;

    bIsLeftArm = (MoveCount % 2 != 0);

    SetTargetLocation(GetActorLocation() + Offset);
    FSM.ChangeState(APlayerState::WALK);
}

void APlayer::UpdateMovement(float _DeltaTime) {
    WalkTime += _DeltaTime;

    FVector2D CurrentLocation = GetActorLocation();
    if ((TargetLocation - CurrentLocation).Length() < 0.1f) {
        SetActorLocation(TargetLocation);
        IsMoving = false;
        FSM.ChangeState(APlayerState::IDLE);
    }
    else {
        FVector2D NewLocation = UPokemonMath::Lerp(CurrentLocation, TargetLocation, WalkTime / TileMoveTime);
        SetActorLocation(NewLocation);

        if (WalkTime >= 0.4f) 
        {
            ChangeArmAnimation();
            WalkTime -= 0.4f; 
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

void APlayer::ChangeArmAnimation() {
    std::string AnimationName;

    switch (CurDir)
    {
    case EPlayerDir::RIGHT_Left_Arm:
    case EPlayerDir::RIGHT_Right_Arm:
        AnimationName = (CurDir == EPlayerDir::RIGHT_Left_Arm) ? "Walk_Right_Left_Arm" : "Walk_Right_Right_Arm";
        break;

    case EPlayerDir::LEFT_Left_Arm:
    case EPlayerDir::LEFT_Right_Arm:
        AnimationName = (CurDir == EPlayerDir::LEFT_Left_Arm) ? "Walk_Left_Left_Arm" : "Walk_Left_Right_Arm";
        break;

    case EPlayerDir::DOWN_Left_Arm:
    case EPlayerDir::DOWN_Right_Arm:
        AnimationName = (CurDir == EPlayerDir::DOWN_Left_Arm) ? "Walk_Down_Left_Arm" : "Walk_Down_Right_Arm";
        break;

    case EPlayerDir::UP_Left_Arm:
    case EPlayerDir::UP_Right_Arm:
        AnimationName = (CurDir == EPlayerDir::UP_Left_Arm) ? "Walk_Up_Left_Arm" : "Walk_Up_Right_Arm";
        break;

    default:
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
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

    GetWorld()->SetCameraPos(UPokemonMath::Lerp(GetWorld()->GetCameraPos(), NewCameraPos, static_cast<float>(WalkSpeed) * 0.5f));
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

    if (UEngineInput::GetInst().IsDown('S'))
    {
        NextDirection = APlayer::EPlayerDir::DOWN_Left_Arm;
    }
    else if (UEngineInput::GetInst().IsDown('W'))
    {
        NextDirection = APlayer::EPlayerDir::UP_Left_Arm;
    }
    else if (UEngineInput::GetInst().IsDown('A'))
    {
        NextDirection = APlayer::EPlayerDir::LEFT_Left_Arm;
    }
    else if (UEngineInput::GetInst().IsDown('D'))
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
    WalkTime = 0.0f;

    PlayerGroundCheck(TargetLocation);

    if (CheckColor != UColor::RED)
    {
        IsMoving = true;
    }
    else
    {
        IsMoving = false;
        TargetLocation = GetActorLocation(); 
    }
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

        if (CheckColor == UColor::RED)
        {
            IsMoving = false;
            TargetLocation = GetActorLocation(); 
        }
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
    SpriteRenderer->SetComponentScale({ 300 , 300 });
}


void APlayer::InitializeAnimations()
{
    float FrameTime = TileMoveTime / 0.8f; 

    SpriteRenderer->CreateAnimation("Walk_Up_Left_Arm", "Player_Walk_Up.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Up_Right_Arm", "Player_Walk_Up.png", 3, 4, FrameTime);

    SpriteRenderer->CreateAnimation("Walk_Down_Left_Arm", "Player_Walk_Down.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Down_Right_Arm", "Player_Walk_Down.png", 3, 4, FrameTime);

    SpriteRenderer->CreateAnimation("Walk_Right_Left_Arm", "Player_Walk_Right.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Right_Right_Arm", "Player_Walk_Right.png", 3, 4, FrameTime);

    SpriteRenderer->CreateAnimation("Walk_Left_Left_Arm", "Player_Walk_Left.png", 1, 2, FrameTime);
    SpriteRenderer->CreateAnimation("Walk_Left_Right_Arm", "Player_Walk_Left.png", 3, 4, FrameTime);

    SpriteRenderer->CreateAnimation("Jump", "Player_Walk_Down.png", 3, 3, FrameTime);


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


void APlayer::SetDirection(EPlayerDir NewDirection)
{
    CurDir = NewDirection;

    std::string AnimationName;

    switch (CurDir)
    {
    case EPlayerDir::RIGHT_Left_Arm:
    case EPlayerDir::RIGHT_Right_Arm:
        AnimationName = "Idle_Right_Left_Arm";
        break;

    case EPlayerDir::LEFT_Left_Arm:
    case EPlayerDir::LEFT_Right_Arm:
        AnimationName = "Idle_Left_Left_Arm";
        break;

    case EPlayerDir::UP_Left_Arm:
    case EPlayerDir::UP_Right_Arm:
        AnimationName = "Idle_Up_Left_Arm";
        break;

    case EPlayerDir::DOWN_Left_Arm:
    case EPlayerDir::DOWN_Right_Arm:
        AnimationName = "Idle_Down_Left_Arm";
        break;

    default:
        break;
    }

    SpriteRenderer->ChangeAnimation(AnimationName);
}

void APlayer::MoveToTile(const FVector2D& TargetTile)
{
    FVector2D TileSize = FVector2D(96.0f, 96.0f);
    FVector2D TargetPosition = FVector2D(
        TargetTile.X * TileSize.X,
        TargetTile.Y * TileSize.Y
    );

    FVector2D Offset = TargetPosition - GetActorLocation();

    if (Offset.X > 0)
        CurDir = bIsLeftArm ? EPlayerDir::RIGHT_Left_Arm : EPlayerDir::RIGHT_Right_Arm;
    else if (Offset.X < 0)
        CurDir = bIsLeftArm ? EPlayerDir::LEFT_Left_Arm : EPlayerDir::LEFT_Right_Arm;
    else if (Offset.Y > 0)
        CurDir = bIsLeftArm ? EPlayerDir::DOWN_Left_Arm : EPlayerDir::DOWN_Right_Arm;
    else if (Offset.Y < 0)
        CurDir = bIsLeftArm ? EPlayerDir::UP_Left_Arm : EPlayerDir::UP_Right_Arm;

    bIsLeftArm = !bIsLeftArm; 

    SetTargetLocation(TargetPosition); 
    IsMoving = true;                   
    FSM.ChangeState(APlayerState::WALK);
}


void APlayer::Jump()
{
    if (!CanJump())
    {
        return;
    }

    FVector2D StartPosition = GetActorLocation();
    FVector2D MidJumpPosition = StartPosition + FVector2D(0.0f, TileSize.Y); 
    FVector2D JumpTarget = StartPosition + FVector2D(0.0f, 2.0f * TileSize.Y); 

    UColor MidJumpColor = ColImage->GetColor(MidJumpPosition);

    if (MidJumpColor == UColor::BLUE)
    {
        TargetLocation = JumpTarget;
        IsJumping = true;
        JumpTime = 0.0f;

        SpriteRenderer->ChangeAnimation("Jump");
    }
    else
    {
        IsJumping = false; 
    }
}




void APlayer::UpdateJump(float DeltaTime)
{
    if (!IsJumping)
    {
        return;
    }

    JumpTime += DeltaTime;
    float JumpProgress = JumpTime / JumpDuration; 

    if (JumpProgress < 1.0f) 
    {
        FVector2D CurrentLocation = UPokemonMath::Lerp(GetActorLocation(), TargetLocation, JumpProgress);
        SetActorLocation(CurrentLocation);
    }
    else 
    {
        SetActorLocation(TargetLocation);
        IsJumping = false;

        SpriteRenderer->ChangeAnimation("Idle" + DirString[static_cast<int>(CurDir)]);
    }
}



bool APlayer::CanJump() const
{
    return !IsMoving && !IsJumping && CheckColor == UColor::BLUE;
}

