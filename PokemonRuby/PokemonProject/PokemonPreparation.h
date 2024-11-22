#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineMath.h>

class APokemonPreparation : public AGameMode
{
public:
	APokemonPreparation();
	~APokemonPreparation();

	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

	void BattleGroundSetting();
	void PokemonSetting();
	void PokemonStatUpdate(float _DeltaTime);
	void PokemonReady();
	void PlayerSetting();


	void ThrowBall();
	void ThrowedMonsterBall();
	void ThrowedMosterBall();
	void ThrowMonsterball();
	void SpawnMyPokemonText();

	void SpawnMyPokemon();
	void SpawnPokemon(float _DeltaTime);
	

	void PlayerPokemonUISetting();
	void PlayerPokemonTextSetting();

	void EnemyPokemonUISetting();
	void EnemyPokemonTextSetting();

protected:
	
	class USpriteRenderer* PlayerRenderer = nullptr;
	class USpriteRenderer* MonsterBall = nullptr;

	class AMyPokemon* MyPokemon = nullptr;
	std::string MyPokemonName;

	class AWildPokemon* EnemyPokemon = nullptr;
	class ACursor* Cursor = nullptr;
	class USpriteRenderer* CursorRender = nullptr;

	class USpriteRenderer* Map = nullptr;
	class USpriteRenderer* PlayerPokemonUI = nullptr;
	class USpriteRenderer* EnemyPokemonUI = nullptr;
	class USpriteRenderer* PlayerPokemonShadow = nullptr;
	class USpriteRenderer* EnemyPokemonShadow = nullptr; 

	FVector2D PlayerLocation = FVector2D::ZERO;
	FVector2D MonsterBallLocation = FVector2D::ZERO;

	float ThrowingTime = 0.0f;
	float BallThrowTime = 2.5f;

	bool IsThrowing = false;
	bool IsChatOn = false;
	bool IsBackGroundSetting = false;


	class APokemonText* ChatText = nullptr;
	class APokemonText* MyPokemonStat = nullptr;
	class APokemonText* EnemyPokemonStat = nullptr;

	int PokemonMapLevel = 2;
};
