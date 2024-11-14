#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/GameMode.h>
#include "PokemonEnum.h"

class APokemonBattleMode : public AGameMode
{
public:

	/*std::string_view CapitalString[static_cast<int>(UPokemoncharacter::ECapitals::END)] =
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
		"Z"
	};*/


	// 持失切 社瑚切
	APokemonBattleMode();
	~APokemonBattleMode();

	// delete funcion

	APokemonBattleMode(const APokemonBattleMode& _Other) = delete;
	APokemonBattleMode(APokemonBattleMode&& _Other) noexcept = delete;
	APokemonBattleMode& operator=(const APokemonBattleMode& _Other) = delete;
	APokemonBattleMode& operator=(APokemonBattleMode&& _Other) noexcept = delete;
	
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void SetBackGround();
	void BattleGroundSetting();

	void PokemonSetting();
	void PlayerPokemonUISetting();
	void EnemyPokemonUISetting();

	void PlayerSetting();
	void ThrowMonsterball();
	void SpawnMyPokemon();
	void ThrowedMosterBall();

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	USpriteRenderer* PlayerRenderer = nullptr;
	USpriteRenderer* MonsterBall = nullptr;

	class AMyPokemon* MyPokemon = nullptr;
	class AWildPokemon* EnemyPokemon = nullptr;
	
	USpriteRenderer* PlayerPokemonShadow = nullptr;
	USpriteRenderer* EnemyPokemonShadow = nullptr;
	USpriteRenderer* PlayerPokemonUI = nullptr;
	USpriteRenderer* EnemyPokemonUI = nullptr;

	float ThrowingTime = 0.0f;
	float BallThrowTime = 2.5f;

	bool IsThrow = false;

};

