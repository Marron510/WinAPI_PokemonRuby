#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/GameMode.h>

class APokemonBattleMode : public AGameMode
{
public:
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

	void BattleGroundSetting();

	void PokemonSetting();
	void PlayerPokemonUISetting();
	void EnemyPokemonUISetting();
protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;

	class AMyPokemon* MyPokemon = nullptr;
	class AWildPokemon* EnemyPokemon = nullptr;
	
	USpriteRenderer* PlayerPokemonShadow = nullptr;
	USpriteRenderer* EnemyPokemonShadow = nullptr;
	USpriteRenderer* PlayerPokemonUI = nullptr;
	USpriteRenderer* EnemyPokemonUI = nullptr;

};

