#pragma once
#include <EngineCore/Actor.h>
#include "Cursor.h"
#include <vector>

class PokemonBattleSelect : public AActor
{
private:
	enum ECursorName
	{
		Fight,
		Bag,
		Pokemon,
		Run
	};

	enum class ESubstate
	{
		None,
		Select,
		MoveSelect,
		PokemonSelect,
		ItemSelect,
		CantRunMessage1,
		CantRunMessage2,
		End
	};

public:
	// 持失切 社瑚切
	PokemonBattleSelect();
	~PokemonBattleSelect();

	// delete funcion

	PokemonBattleSelect(const PokemonBattleSelect& _Other) = delete;
	PokemonBattleSelect(PokemonBattleSelect&& _Other) noexcept = delete;
	PokemonBattleSelect& operator=(const PokemonBattleSelect& _Other) = delete;
	PokemonBattleSelect& operator=(PokemonBattleSelect&& _Other) noexcept = delete;


	void BeginPlay() override;

	void Tick(float _DeltaTime) override;


	void HandleInput();

	void UpdateCursorPosition(float DeltaTime);

	void SelectOption();

	int CurrentSelectionIndex = 0;  
	ESubstate CurrentSubstate = ESubstate::None;  
	std::vector<ECursorName> MenuOptions = { ECursorName::Fight, ECursorName::Bag, ECursorName::Pokemon, ECursorName::Run };


protected:

private:

};

