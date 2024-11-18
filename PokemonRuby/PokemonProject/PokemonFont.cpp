#include "PreCompile.h"
#include "PokemonFont.h"



APokemonFont::APokemonFont()
{
}


APokemonFont::~APokemonFont()
{
}

void APokemonFont::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void APokemonFont::BeginPlay()
{
}

void APokemonFont::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PrintTextUpdate(_DeltaTime);
}

void APokemonFont::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void APokemonFont::PrintTextUpdate(float _DeltaTime)
{
	FVector2D Pos = FVector2D::ZERO;

	CurTime -= _DeltaTime;

	if (0.0f > CurTime)
	{
		++CurTextPrint;

		if (CurTextPrint >= PrintText.size())
		{
			CurTextPrint = PrintText.size() - 1;
		}

		CurTime = InterTime;
	}

	for (size_t i = 0; i < CurTextPrint; i++) {
		char Value = PrintText[i];
		int CapitalValue = -1;

		if (Value >= 'A' && Value <= 'Z') {
			CapitalValue = Value - 'A';
		}

		if (CapitalValue != -1 && CapitalValue < static_cast<int>(UPokemoncharacter::ECapitals::END))
		{
			Renders[i]->SetSprite(TextSpriteName, CapitalValue);
			Renders[i]->SetComponentScale(TextScale);
			Renders[i]->SetComponentLocation(Pos);
			Pos.X += TextScale.X;
			Renders[i]->SetActive(true);
		}
		else {
			Renders[i]->SetActive(false);
		}
	}

	for (size_t i = PrintText.size(); i < Renders.size(); i++) {
		Renders[i]->SetActive(false);
	}
}

void APokemonFont::SetFont(std::string_view _Text, float _InterValue /*= 0.0f*/)
{
	

	FVector2D Pos = FVector2D::ZERO;

	PrintText = _Text;

	int Value = _Text.size() - Renders.size();
	if (0 < Value)
	{
		int PrevSize = Renders.size();
		Renders.reserve(_Text.size());

		for (size_t i = PrevSize; i < PrevSize + Value; i++)
		{
			USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
			Sprite->SetCameraEffect(false);
			Sprite->SetActive(false);
			Renders.push_back(Sprite);
		}
	}

	InterTime = _InterValue;

	if (0 >= InterTime)
	{
		CurTime = 0.0f;
		CurTextPrint = _Text.size();
	}

}