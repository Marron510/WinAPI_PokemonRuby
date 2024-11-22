#include "PreCompile.h"
#include "PokemonPreparation.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EngineCore/SpriteRenderer.h>


#include "MyPokemon.h"
#include "WildPokemon.h"
#include "PokemonText.h"
#include "Cursor.h"
#include "PokemonBattleMap.h"

APokemonPreparation::APokemonPreparation()
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
        MonsterBall->SetOrder(ERenderOrder::UI);

        MonsterBall->ChangeAnimation("ThrowBallReady");
    }


}

APokemonPreparation::~APokemonPreparation()
{
}





void APokemonPreparation::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    BattleGroundSetting();
    PokemonSetting();
    PokemonStatUpdate(_DeltaTime);
    PlayerSetting();
}

void APokemonPreparation::BeginPlay()
{
    Super::BeginPlay();
    PokemonReady();
    // 초기화: 적 포켓몬, 내 포켓몬, 커서, 텍스트
    EnemyPokemon = GetWorld()->SpawnActor<AWildPokemon>();
    EnemyPokemon->SetActorLocation({ -312.0f , 260.0f });
    EnemyPokemon->EncounterWildPokemon(PokemonMapLevel);

    MyPokemon = GetWorld()->SpawnActor<AMyPokemon>();
    MyPokemon->SetActorLocation({ -500.0f, -500.0f });
    MyPokemonName = MyPokemon->GetMyPokemonName();

    ChatText = GetWorld()->SpawnActor<APokemonText>();
    ChatText->SetActorLocation({ 100.0f, 640.0f });
    ChatText->SetTextSpriteName("TextWhite.png");
    ChatText->SetTextScale({ 30, 40 });
    ChatText->SetText("Wild " + EnemyPokemon->GetPokemonName() + " appeared!", 0.05f);
    ChatText->SetOrder(ERenderOrder::FONT);

    // 포켓몬 및 UI 설정
    EnemyPokemonStat = GetWorld()->SpawnActor<APokemonText>();
    EnemyPokemonStat->SetTextSpriteName("TextBlack.png");
    EnemyPokemonStat->SetTextScale({ 26, 36 });
    EnemyPokemonStat->SetText(EnemyPokemon->GetPokemonName());
    EnemyPokemonStat->SetActorLocation({ -600.0f , 135.0f });
    EnemyPokemonStat->SetOrder(ERenderOrder::FONT);

    MyPokemonStat = GetWorld()->SpawnActor<APokemonText>();
    MyPokemonStat->SetTextSpriteName("TextBlack.png");
    MyPokemonStat->SetTextScale({ 26, 36 });
    MyPokemonStat->SetText(MyPokemonName);
    MyPokemonStat->SetActorLocation({ 1440.0f , 415.0f });
    MyPokemonStat->SetOrder(ERenderOrder::FONT);

   
}

void APokemonPreparation::PokemonStatUpdate(float _DeltaTime)
{
    EnemyPokemonStat->PrintTextUpdate(_DeltaTime);
    MyPokemonStat->PrintTextUpdate(_DeltaTime);
    ChatText->PrintTextUpdate(_DeltaTime);;
   /* if (true == IsBattleNow)
    {
        MyPokemonSkill1->PrintTextUpdate(_DeltaTime);
        MyPokemonSkill2->PrintTextUpdate(_DeltaTime);
        MyPokemonSkill3->PrintTextUpdate(_DeltaTime);
        MyPokemonSkill4->PrintTextUpdate(_DeltaTime);
    }*/

}


void APokemonPreparation::PokemonReady()
{
    APokemonBattleMap* BackImage = GetWorld()->SpawnActor<APokemonBattleMap>();

    Map = BackImage->GetCurMap();
    PlayerPokemonUI = BackImage->GetPokemonUI();
    EnemyPokemonUI = BackImage->GetEnemyPokemonUI();
    PlayerPokemonShadow = BackImage->GetPlayerPKMShadow();
    EnemyPokemonShadow = BackImage->GetEnemyPokemonShadow();
}

void APokemonPreparation::BattleGroundSetting()
{
    {
        FVector2D TargetLocation = FVector2D({ 336.0f , 520.0f }); // PlayerPokemonShadow의 최종 목적지
        FVector2D Curloc = PlayerPokemonShadow->GetComponentLocation();
        Curloc += FVector2D::LEFT.Half();
        if (TargetLocation == Curloc)
        {
            PlayerPokemonShadow->GetComponentLocation() = TargetLocation;
            IsBackGroundSetting = true;
            return;
        }

        PlayerPokemonShadow->SetComponentLocation(Curloc);
    }

    {
        FVector2D EnemyShadowTargetLocation = FVector2D({ 840.0f , 308.0f }); // EnemyPokemonShadow의 최종 목적지
        FVector2D EnemyCurloc = EnemyPokemonShadow->GetComponentLocation();

        if (EnemyShadowTargetLocation == EnemyCurloc)
        {
            EnemyPokemonShadow->GetComponentLocation() = EnemyShadowTargetLocation;
            return;
        }

        EnemyCurloc += FVector2D::RIGHT.Half();
        EnemyPokemonShadow->SetComponentLocation(EnemyCurloc);
    }

}

void APokemonPreparation::PokemonSetting()
{
    {
        FVector2D TargetLocation = FVector2D({ 862.0f , 260.0f });
        FVector2D Curloc = EnemyPokemon->GetActorLocation();
        Curloc += FVector2D::RIGHT.Half();

        if (TargetLocation == Curloc)
        {
            EnemyPokemon->GetActorLocation() = TargetLocation;
            EnemyPokemonUISetting();
            EnemyPokemonTextSetting();
            return;
        }

        EnemyPokemon->SetActorLocation(Curloc);
    }
}


void APokemonPreparation::EnemyPokemonUISetting()
{
    FVector2D TargetLocation = FVector2D({ 336.0f , 166.0f }); // EnemyPokemonUI의 최종 목적지
    FVector2D Curloc = EnemyPokemonUI->GetComponentLocation();

    Curloc += FVector2D::RIGHT;
    if (TargetLocation == Curloc)
    {
        EnemyPokemonUI->GetComponentLocation() = TargetLocation;
        return;
    }

    EnemyPokemonUI->SetComponentLocation(Curloc);
}

void APokemonPreparation::EnemyPokemonTextSetting()
{
    FVector2D TargetLocation = FVector2D({ 130.0f , 135.0f });
    FVector2D Curloc = EnemyPokemonStat->GetActorLocation();

    Curloc += FVector2D::RIGHT;

    if (TargetLocation == Curloc)
    {
        EnemyPokemonStat->GetActorLocation() = TargetLocation;
        return;
    }

    EnemyPokemonStat->SetActorLocation(Curloc);
}



void APokemonPreparation::ThrowBall()
{
    FVector2D TargetLocation = FVector2D({ -100.0f ,416.0f });
    PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBall");
    PlayerLocation = PlayerRenderer->GetComponentLocation();
    PlayerLocation += FVector2D::LEFT * 2;
    PlayerRenderer->SetComponentLocation(PlayerLocation);
    IsChatOn = true;

    // 몬스터볼 애니메이션 시작
    MonsterBall->ChangeAnimation("ThrowBall");
    ThrowedMonsterBall();

    // 포켓몬 텍스트 변경
    ChatText->SetText("Go " + MyPokemonName + "!", 0.01f);
}

void APokemonPreparation::ThrowedMonsterBall()
{
    MonsterBall->SetComponentLocation({ 300 , 420 });
}

void APokemonPreparation::SpawnMyPokemon()
{
    if (-300 > PlayerLocation.X)
    {
        MyPokemon->SetActorLocation({ 336 ,416 });
        PlayerRenderer->SetActive(false);
        PlayerPokemonUISetting();
        PlayerPokemonTextSetting();
    }
}

void APokemonPreparation::PlayerPokemonUISetting()
{
    FVector2D TargetLocation = FVector2D({ 902.0f , 460.0f });
    FVector2D Curloc = PlayerPokemonUI->GetComponentLocation();
    Curloc += FVector2D::LEFT;

    if (TargetLocation == Curloc)
    {
        PlayerPokemonUI->GetComponentLocation() = TargetLocation;
        return;
    }

    PlayerPokemonUI->SetComponentLocation(Curloc);
}

void APokemonPreparation::PlayerPokemonTextSetting()
{
    FVector2D TargetLocation = FVector2D({ 740.0f , 415.0f });
    FVector2D Curloc = MyPokemonStat->GetActorLocation();

    Curloc += FVector2D::LEFT;

    if (TargetLocation == Curloc)
    {
        MyPokemonStat->GetActorLocation() = TargetLocation;
        IsChatOn = false;
        //open level pokemonbattlemenuselect
        return;
    }

    MyPokemonStat->SetActorLocation(Curloc);
}


void APokemonPreparation::PlayerSetting()
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



void APokemonPreparation::SpawnPokemon(float _DeltaTime)
{
    if (true == IsBackGroundSetting)
    {
        ChatText->PrintTextUpdate(_DeltaTime);
    }

    if (UEngineInput::GetInst().IsDown('Z'))
    {
        ThrowMonsterball();
        MonsterBall->ChangeAnimation("ThrowBall");
        ThrowedMosterBall();
    }

    SpawnMyPokemonText();
    SpawnMyPokemon();


}

void APokemonPreparation::ThrowMonsterball()
{
    FVector2D TargetLocation = FVector2D({ -100.0f ,416.0f });
    PlayerRenderer->ChangeAnimation("PlayerThrowMonsterBall");
    PlayerLocation = PlayerRenderer->GetComponentLocation();
    PlayerLocation += FVector2D::LEFT * 2;
    PlayerRenderer->SetComponentLocation(PlayerLocation);
    IsChatOn = true;
}



void APokemonPreparation::SpawnMyPokemonText()
{
    if (IsChatOn == true)
    {
        ChatText->SetText("Go " + MyPokemonName + "!", 0.01f);
    }
}

void APokemonPreparation::ThrowedMosterBall()
{
    MonsterBall->SetComponentLocation({ 300 , 420 });
}

