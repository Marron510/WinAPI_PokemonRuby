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
		Renders[i]->SetSprite(TextSpriteName);
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
    FVector2D Pos = FVector2D::ZERO;  // 첫 번째 글자의 위치 (초기 위치)
    float InitialPosX = Pos.X;  // 처음 위치를 저장해두고, 줄바꿈 시에 다시 돌아오도록 함
    CurTime -= _DeltaTime;

    if (CurTime <= 0.0f) {
        ++CurTextPrint;

        if (CurTextPrint >= GetTotalTextSize()) {
            CurTextPrint = GetTotalTextSize();
        }

        CurTime = InterTime;
    }

    int printCount = 0;
    float spriteHeight = TextScale.Y; // TextScale.Y가 스프라이트의 높이를 나타낸다고 가정

    for (size_t j = 0; j < PrintTexts.size(); ++j) {
        const std::string& Text = PrintTexts[j];

        for (size_t i = 0; i < Text.size(); ++i) {
            if (printCount >= CurTextPrint) {
                break;
            }

            char Value = Text[i];
            int CapitalValue = -1;

            // 줄바꿈 문자인 "\n"을 만나면 첫 번째 위치로 돌아가고, 수직으로 1.2배 만큼 이동
            if (Value == '\n') {
                Pos.X = InitialPosX; // 첫 번째 문자의 X 위치로 돌아감
                Pos.Y += spriteHeight * 1.2f; // 1.2배 만큼 아래로 이동
                continue;  // 줄바꿈 문자는 출력되지 않음
            }

            // 각 문자의 CapitalValue를 결정
            if (Value >= 'A' && Value <= 'Z') {
                CapitalValue = Value - 'A';
            }
            else if (Value >= 'a' && Value <= 'z') {
                CapitalValue = Value - 'a' + 26;
            }
            else if (Value == ' ') {
                CapitalValue = Value - ' ' + 52;
            }
            else if (Value == ',') {
                CapitalValue = Value - ',' + 53;
            }
            else if (Value == '.') {
                CapitalValue = Value - '.' + 54;
            }
            else if (Value == '!') {
                CapitalValue = Value - '!' + 65;
            }
            else if (Value == '?') {
                CapitalValue = Value - '?' + 66;
            }
            else if (Value == '♂') {
                CapitalValue = Value - '♂' + 67;
            }
            else if (Value == '♀') {
                CapitalValue = Value - '♀' + 68;
            }
            else if (Value == '\/') {
                CapitalValue = Value - '\/' + 69;
            }
            else if (Value == '\"') {
                CapitalValue = Value - '\"' + 71;
            }
            else if (Value == '\'') {
                CapitalValue = Value - '\'' + 73;
            }

            if (CapitalValue != -1 && CapitalValue < static_cast<int>(UPokemoncharacter::ECapitals::END)) {
                Renders[printCount]->SetSprite(TextSpriteName, CapitalValue);
                Renders[printCount]->SetComponentScale(TextScale);
                Renders[printCount]->SetComponentLocation(Pos);
                Pos.X += TextScale.X;  // 스프라이트의 가로 크기만큼 수평 이동
                TextSize += 1;
                Renders[printCount]->SetActive(true);
            }

            ++printCount;
        }
    }

    // 나머지 문자는 비활성화
    for (size_t i = printCount; i < Renders.size(); ++i) {
        Renders[i]->SetActive(false);
    }
}





void APokemonText::SetText(std::string_view _Text, float _InterValue /*= 0.0f*/)
{
    PrintTexts.clear();

    PrintTexts.push_back(std::string(_Text));  

    int Value = _Text.size() - Renders.size();
    if (Value > 0)
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

    if (InterTime <= 0.0f) {
        CurTime = 0.0f;
        CurTextPrint = _Text.size(); 
    }
}


void APokemonText::ClearText()
{
    PrintTexts.clear();
    CurTextPrint = 0;

    for (size_t i = 0; i < Renders.size(); i++) {
        Renders[i]->SetActive(false);
    }

    Renders.clear();

    CurTime = 0.0f;
    TextSize = 0;
}


int APokemonText::GetTotalTextSize() const
{
    int size = 0;
    for (const auto& Text : PrintTexts) {
        size += Text.size();
    }
    return size;
}