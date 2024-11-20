#include "PreCompile.h"
#include "MyPokemon.h"


#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

AMyPokemon::AMyPokemon()
{
	Treecko = CreateDefaultSubObject<USpriteRenderer>();
	Treecko->SetOrder(ERenderOrder::POKEMON);
	Treecko->SetSprite("Treecko.png");
	FVector2D Scale = Treecko->SetSpriteScale(1.0f);
	Treecko->CreateAnimation("Treecko", "Treecko.png", 0, 0, 0.2f);
	
	
	// 포켓몬은 맵으로 만들어서 관리?
	// 커서를 포켓몬이 가지는 형식으로
}


AMyPokemon::~AMyPokemon()
{

}


void AMyPokemon::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPokemon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

//
//AMyPokemon::AMyPokemon()
//{
//    //Lv = 5; // 초기 레벨
//    //MaxHP = 100;
//    //PHp = MaxHP;
//    //PAtk = 50;  
//    //PDef = 40; 
//    //Pspeed = 30;
//    //PSpAtk = 40; 
//    //PSpDef = 40; 
//
//    //PKMSkills.push_back("Pound");
//    //PKMSkills.push_back("QuickAttack");
//
//    //UpdateStats();
//}

// 레벨업 함수
void AMyPokemon::LevelUp(int levels)
{
    for (int i = 0; i < levels; ++i)
    {
        Lv++;
        PAtk += 5;  
        PDef += 3; 
        Pspeed += 2; 
        PSpAtk += 4; 
        PSpDef += 3; 
    }

    UpdateStats();
}

// 능력치 계산 함수 (개체값, 노력치 반영)
void AMyPokemon::UpdateStats()
{
    // 예시: 기본 능력치 + 개체값 + 노력치에 따른 변화
    PAtk += IValue + EVs / 4;
    PDef += IValue + EVs / 4;
   
}

