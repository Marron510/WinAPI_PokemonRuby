#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/GameMode.h>
#include "PokemonEnum.h"

class APokemonBattleMode : public AGameMode
{
public:

	


	// 생성자 소멸자
	APokemonBattleMode();
	~APokemonBattleMode();

	// delete funcion

	APokemonBattleMode(const APokemonBattleMode& _Other) = delete;
	APokemonBattleMode(APokemonBattleMode&& _Other) noexcept = delete;
	APokemonBattleMode& operator=(const APokemonBattleMode& _Other) = delete;
	APokemonBattleMode& operator=(APokemonBattleMode&& _Other) noexcept = delete;
	
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void APokemonPreparation();
	void BattleGroundSetting();

	void PokemonSetting();
	void PlayerPokemonUISetting();
	void PlayerPokemonTextSetting();
	void EnemyPokemonUISetting();
	void EnemyPokemonTextSetting();
	void PokemonStatUpdate(float _delatime);
	void SpawnSelectMenu();
	void SpawnBattleSelectMenu();
	void HandleSkillSelection(FVector2D CursorLocation);
	void PlayerSetting();
	void ThrowMonsterball();
	void SpawnPokemon(float _DeltaTime);
	void SpawnMyPokemon();
	void SpawnMyPokemonText();
	void ThrowedMosterBall();
	void StartEnemyTurn();

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	USpriteRenderer* PlayerRenderer = nullptr;
	USpriteRenderer* MonsterBall = nullptr;

	class AMyPokemon* MyPokemon = nullptr;
	std::string MyPokemonName;


	class AWildPokemon* EnemyPokemon = nullptr;
	class ACursor* Cursor = nullptr;
	USpriteRenderer* CursorRender = nullptr;
	USpriteRenderer* PlayerPokemonShadow = nullptr;
	USpriteRenderer* EnemyPokemonShadow = nullptr;
	USpriteRenderer* PlayerPokemonUI = nullptr;
	USpriteRenderer* EnemyPokemonUI = nullptr;
	USpriteRenderer* SelectMenu = nullptr;
	USpriteRenderer* BattleSelectMenu = nullptr;


	FVector2D PlayerLocation = FVector2D::ZERO;
	
	FVector2D MosterBallLocation = FVector2D::ZERO;



	float ThrowingTime = 0.0f;
	float BallThrowTime = 2.5f;


	bool IsBackGroundSetting = false;
	bool IsThrowing = false;   
	bool IsChatOn = false;
	bool IsMenuOn = false;
	bool IsBattleNow = false;
	bool IsBattleCursorSet = false;
	bool IsPlayerTurn = true;  // 플레이어 턴이면 true, 상대 턴이면 false
	bool IsFirstZKeyPressed = false;

	class APokemonText* ChatText = nullptr;
	class APokemonText* MyPokemonStat = nullptr;
	class APokemonText* MyPokemonSkill1 = nullptr;
	class APokemonText* MyPokemonSkill2 = nullptr;
	class APokemonText* MyPokemonSkill3 = nullptr;
	class APokemonText* MyPokemonSkill4 = nullptr;



	class APokemonText* EnemyPokemonStat = nullptr;
		
	bool bHasDisplayedMenuText = false;
	int PokemonMapLevel = 2;
};

