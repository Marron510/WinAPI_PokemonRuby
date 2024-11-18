#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

#include "PokemonEnum.h"

class APokemonText : public AActor
{
public:
	std::string_view CapitalString[static_cast<int>(UPokemoncharacter::ECapitals::END)] =
	{
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"a",
		"b",
		"c",
		"d",
		"e",
		"f",
		"g",
		"h",
		"i",
		"j",
		"k",
		"l",
		"m",
		"n",
		"o",
		"p",
		"q",
		"r",
		"s",
		"t",
		"u",
		"v",
		"w",
		"x",
		"y",
		"z",
		" ",
		",",
		".",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"!",
		"?",
		"［",
		"］",
		"/",
		"\"",
		"\"",
		"\'",
		"\'"
	};

	// 持失切 社瑚切
	APokemonText();
	~APokemonText();

	// delete funcion

	APokemonText(const APokemonText& _Other) = delete;
	APokemonText(APokemonText&& _Other) noexcept = delete;
	APokemonText& operator=(const APokemonText& _Other) = delete;
	APokemonText& operator=(APokemonText&& _Other) noexcept = delete;
	
	
	void BeginPlay();
	void Tick(float _DeltaTime);

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetText(std::string_view _Text, float _InterValue = 0.0f);

	// void SetFont(std::vector<std::string_view> _Text, float _InterValue = 0.0f);

	void PrintTextUpdate(float _DeltaTime);

	void IsEnd();

protected:

private:
	int CurTextPrint = 0;
	float InterTime = 0.0;
	float CurTime = 0.0;
	std::string PrintText;
	// std::vector<std::string> PrintTexts;

	std::string TextSpriteName;
	FVector2D TextScale;
	std::vector<class USpriteRenderer*> Renders;
};

