#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include "MyPokemon.h"

namespace GameData 
{
	extern AMyPokemon::EMyPokemon SelectedPokemon;
}

class ASelectPokemonMode : public AGameMode
{
public:

	const FVector2D Positions[3] = {
		{ 300, 170 },
		{ 600, 320 },
		{ 900, 170 }
	};


	// 持失切 社瑚切
	ASelectPokemonMode();
	~ASelectPokemonMode();

	// delete funcion

	ASelectPokemonMode(const ASelectPokemonMode& _Other) = delete;
	ASelectPokemonMode(ASelectPokemonMode&& _Other) noexcept = delete;
	ASelectPokemonMode& operator=(const ASelectPokemonMode& _Other) = delete;
	ASelectPokemonMode& operator=(ASelectPokemonMode&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CursorMove();
	void NameRender();
	void SelectPokemon();
	// void OnPokemonSelected(AMyPokemon::EMyPokemon SelectedPokemon);


protected:

private:
	class USpriteRenderer* SelectCursor = nullptr;

	class USpriteRenderer* SelectTreecko = nullptr;
	class USpriteRenderer* SelectTorchic = nullptr;
	class USpriteRenderer* SelectMudkip = nullptr;

	class USpriteRenderer* Pokeball1 = nullptr;
	class USpriteRenderer* Pokeball2 = nullptr;
	class USpriteRenderer* Pokeball3 = nullptr;

	class AMyPokemon* MyPokemon = nullptr;

	class AFade* Fade = nullptr;

	class USoundPlayer BGMPlayer;

	int CurrentIndex = 0;
	
};

