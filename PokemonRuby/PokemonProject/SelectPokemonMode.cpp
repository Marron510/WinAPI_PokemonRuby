#include "PreCompile.h"
#include "SelectPokemonMode.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "PokemonEnum.h"
#include "SelectPokemonMap.h"

ASelectPokemonMode::ASelectPokemonMode()
{
	
}

ASelectPokemonMode::~ASelectPokemonMode()
{

}

void ASelectPokemonMode::BeginPlay()
{

	{
		ASelectPokemonMap* NewActor = GetWorld()->SpawnActor<ASelectPokemonMap>();
		Map = NewActor->GetCurMap();
	}

	{
		Pokeball1 = CreateDefaultSubObject<USpriteRenderer>();
		Pokeball1->SetSprite("SelectBall.png");
		Pokeball1->SetComponentScale({ 100 , 100 });

		Pokeball1->CreateAnimation("SelectBallCursor", "SelectBall.png", 0, 5, 0.1f);
		Pokeball1->CreateAnimation("SelectBall", "SelectBall.png", 0, 0, 0.1f);

		Pokeball1->ChangeAnimation("SelectBall");
		Pokeball1->SetOrder(ERenderOrder::NPC);
		Pokeball1->SetComponentLocation({ 300,300 });
	}
	{
		Pokeball2 = CreateDefaultSubObject<USpriteRenderer>();
		Pokeball2->SetSprite("SelectBall.png");
		Pokeball2->SetComponentScale({ 100 , 100 });

		Pokeball2->CreateAnimation("SelectBallCursor", "SelectBall.png", 0, 5, 0.1f);
		Pokeball2->CreateAnimation("SelectBall", "SelectBall.png", 0, 0, 0.1f);

		Pokeball2->ChangeAnimation("SelectBall");
		Pokeball2->SetOrder(ERenderOrder::NPC);
		Pokeball2->SetComponentLocation({ 600,450 });
	}
	{
		Pokeball3 = CreateDefaultSubObject<USpriteRenderer>();
		Pokeball3->SetSprite("SelectBall.png");
		Pokeball3->SetComponentScale({ 100 , 100 });

		Pokeball3->CreateAnimation("SelectBallCursor", "SelectBall.png", 0, 5, 0.1f);
		Pokeball3->CreateAnimation("SelectBall", "SelectBall.png", 0, 0, 0.1f);

		Pokeball3->ChangeAnimation("SelectBall");
		Pokeball3->SetOrder(ERenderOrder::NPC);
		Pokeball3->SetComponentLocation({ 900,300 });
	}

	{
		SelectCursor = CreateDefaultSubObject<USpriteRenderer>();
		SelectCursor->SetSprite("SelectCursor.png");
		SelectCursor->SetComponentScale({ 100 , 100 });

		SelectCursor->CreateAnimation("SelectCursor", "SelectCursor.png", 0, 3, 0.15f);

		SelectCursor->ChangeAnimation("SelectCursor");
		SelectCursor->SetOrder(ERenderOrder::NPC);
		SelectCursor->SetComponentLocation({ 300,150 });
	}

	{
		SelectTreecko = CreateDefaultSubObject<USpriteRenderer>();
		SelectTreecko->SetSprite("SelectTreecko.png");
		SelectTreecko->SetComponentScale({ 500 , 200 });

		SelectTreecko->CreateAnimation("SelectTreecko", "SelectTreecko.png", 0, 0, 0.1f);

		SelectTreecko->ChangeAnimation("SelectTreecko");
		SelectTreecko->SetOrder(ERenderOrder::NPC);
		SelectTreecko->SetComponentLocation({ 290,465 });
	}
	{
		SelectTorchic = CreateDefaultSubObject<USpriteRenderer>();
		SelectTorchic->SetSprite("SelectTorchic.png");
		SelectTorchic->SetComponentScale({ 500 , 200 });

		SelectTorchic->CreateAnimation("SelectTorchic", "SelectTorchic.png", 0, 0, 0.1f);

		SelectTorchic->ChangeAnimation("SelectTorchic");
		SelectTorchic->SetOrder(ERenderOrder::NPC);
		SelectTorchic->SetComponentLocation({ 600, 120 });
	}
	{
		SelectMudkip = CreateDefaultSubObject<USpriteRenderer>();
		SelectMudkip->SetSprite("SelectMudkip.png");
		SelectMudkip->SetComponentScale({ 500 , 200 });

		SelectMudkip->CreateAnimation("SelectMudkip", "SelectMudkip.png", 0, 0, 0.1f);

		SelectMudkip->ChangeAnimation("SelectMudkip");
		SelectMudkip->SetOrder(ERenderOrder::NPC);
		SelectMudkip->SetComponentLocation({ 900,465 });
	}
}

void ASelectPokemonMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	CursorMove();
	NameRender();
}

void ASelectPokemonMode::CursorMove()
{
	
	if (UEngineInput::GetInst().IsDown('A'))
	{
		CurrentIndex = (CurrentIndex - 1 + 3) % 3; 
	}
	else if (UEngineInput::GetInst().IsDown('D'))
	{
		CurrentIndex = (CurrentIndex + 1) % 3; 
	}

	SelectCursor->SetComponentLocation(Positions[CurrentIndex]);
}


void ASelectPokemonMode::NameRender()
{
	if (0 == CurrentIndex)
	{
		SelectTreecko->SetActive(true);
		SelectTorchic->SetActive(false);
		SelectMudkip->SetActive(false);
		Pokeball1->ChangeAnimation("SelectBallCursor");
		Pokeball2->ChangeAnimation("SelectBall");
		Pokeball3->ChangeAnimation("SelectBall");
	}
	else if (1 == CurrentIndex)
	{
		SelectTreecko->SetActive(false);
		SelectTorchic->SetActive(true);
		SelectMudkip->SetActive(false);
		Pokeball1->ChangeAnimation("SelectBall");
		Pokeball2->ChangeAnimation("SelectBallCursor");
		Pokeball3->ChangeAnimation("SelectBall");
	}
	else if (2 == CurrentIndex)
	{
		SelectTreecko->SetActive(false);
		SelectTorchic->SetActive(false);
		SelectMudkip->SetActive(true);
		Pokeball1->ChangeAnimation("SelectBall");
		Pokeball2->ChangeAnimation("SelectBall");
		Pokeball3->ChangeAnimation("SelectBallCursor");
	}
}

