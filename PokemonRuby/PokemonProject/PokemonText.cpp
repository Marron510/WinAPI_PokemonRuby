#include "PreCompile.h"
#include "PokemonText.h"
#include "Cursor.h"

int APokemonText::TextSize = 0;

APokemonText::APokemonText()
{
}


APokemonText::~APokemonText()
{
}

void APokemonText::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetPKMSprite(TextSpriteName);
	}
}

void APokemonText::BeginPlay()
{
}

void APokemonText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//PrintTextUpdate(_DeltaTime);
}

void APokemonText::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void APokemonText::PrintTextUpdate(float _DeltaTime)
{
	FVector2D Pos = FVector2D::ZERO;

	CurTime -= _DeltaTime;

	if (0.0f > CurTime)
	{
		++CurTextPrint;

		if (CurTextPrint >= PrintText.size())
		{
			CurTextPrint = PrintText.size();
		}

		CurTime = InterTime;
	}

	for (size_t i = 0; i < CurTextPrint; i++) {
		char Value = PrintText[i];
		int CapitalValue = -1;

		if (Value >= 'A' && Value <= 'Z') 
		{
			CapitalValue = Value - 'A';
		}
		if (Value >= 'a' && Value <= 'z')
		{
			CapitalValue = Value - 'a' + 26;
		}
		if (Value == ' ')
		{
			CapitalValue = Value - ' ' + 52;
		}

		if (Value == ',')
		{
			CapitalValue = Value - ',' + 53;
		}

		if (Value == '.')
		{
			CapitalValue = Value - '.' + 54;
		}

		if (Value == '!')
		{
			CapitalValue = Value - '!' + 65;
		}

		if (Value == '?')
		{
			CapitalValue = Value - '?' + 66;
		}

		if (Value == '［')
		{
			CapitalValue = Value - '［' + 67;
		}

		if (Value == '］')
		{
			CapitalValue = Value - '］' + 68;
		}

		if (Value == '\/')
		{
			CapitalValue = Value - '\/' + 69;
		}

		if (Value == '\"')
		{
			CapitalValue = Value - '\"' + 71;
		}

		if (Value == '\"')
		{
			CapitalValue = Value - '\"' + 72;
		}

		if (Value == '\'')
		{
			CapitalValue = Value - '\'' + 73;
		}

		if (Value == '\'')
		{
			CapitalValue = Value - '\'' + 74;
		}


		if (Value >= '0' && Value <= '9')
		{
			CapitalValue = Value - '0' + 55;
		}

		if (CapitalValue != -1 && CapitalValue < static_cast<int>(UPokemoncharacter::ECapitals::END))
		{
			
			Renders[i]->SetSprite(TextSpriteName, CapitalValue); 
			Renders[i]->SetComponentScale(TextScale);
			Renders[i]->SetComponentLocation(Pos);
			Pos.X += TextScale.X;
			TextSize += 1;
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




void APokemonText::SetText(std::string_view _Text, float _InterValue /*= 0.0f*/)
{
	

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


void APokemonText::ClearText()
{
	PrintText.clear();

	CurTextPrint = 0;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
		
	}

	Renders.clear();
	
	CurTime = 0.0f;

	TextSize = 0;
}

bool APokemonText::IsEnd() const
{
	return CurTextPrint >= PrintText.size();
}