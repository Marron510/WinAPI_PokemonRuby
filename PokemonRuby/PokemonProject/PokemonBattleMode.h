#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>

#include "PokemonEnum.h"

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

	void APokemonPreparation();
	void BattleGroundSetting();

	void PokemonSetting();

	void PlayerPokemonUISetting();
	void PlayerPokemonTextSetting();
	void PlayerPokemonHPSetting();
	void PlayerPokemonLevelTextSetting();
	void PlayerPokemonHPTextSetting();
	void PlayerPokemonMaxHPTextSetting();
	void PlayerPokemonEXPSetting();

	void EnemyPokemonUISetting();
	void EnemyPokemonTextSetting();
	void EnemyPokemonHpSetting();
	void EnemyPokemonLevelTextSetting();

	void PokemonStatUpdate(float _delatime);
	void SpawnSelectMenu();
	void HandleSkillSelection(FVector2D CursorLocation);
	void PlayerSetting();

	void ThrowMonsterball();
	void SpawnPokemon(float _DeltaTime);
	void SpawnMyPokemon();
	void SpawnMyPokemonText();
	void ThrowedMosterBall();

	void SkillTextOff();
	void SkillTextOn();
	void HandleMenuSelection(FVector2D CursorLocation);

	void DisplayChatText();
	void Skill1ChatText();
	void Skill2ChatText();
	void EnemySkill1ChatText();
	void HPCheck(float _DeltaTime);

	void EnemyDeadCheck();
	void EnemyPokemonAttack();
	void EnemypokemonDead();
	void UpdateEXPBar(float _DeltaTime);

	class AMyPokemon* GetMyPokemon()
	{
		return MyPokemon;
	}

	class AWildPokemon* GetEnemyPokemon()
	{
		return EnemyPokemon;
	}

	class APokemonText* GetMyPokemonStat() { return MyPokemonStat; }
	class APokemonText* GetMyPokemonSkill1() { return MyPokemonSkill1; }
	class APokemonText* GetMyPokemonSkill2() { return MyPokemonSkill2; }
	class APokemonText* GetMyPokemonSkill3() { return MyPokemonSkill3; }
	class APokemonText* GetMyPokemonSkill4() { return MyPokemonSkill4; }
	class APokemonText* GetEnemyPokemonStat() { return EnemyPokemonStat; }

	void PokemonBattleLogic1();
	void PokemonBattleLogic2();
	void FailedSkill();

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	USpriteRenderer* PlayerRenderer = nullptr;
	USpriteRenderer* MonsterBall = nullptr;

	class AMyPokemon* MyPokemon = nullptr;

	class APokemonHP* MyPokemonHPbar = nullptr;
	class APokemonHP* EnemyPokemonHPbar = nullptr;

	class APokemonEXP* MyPokemonEXP = nullptr;

	std::string MyPokemonName;
	std::string MyPokemonLevel;
	std::string enter = "\n";
	std::string MyPokemonSkillText;
	std::string EnemyPokemonSkillText;
	std::string EnemyPokemonLevel;


	class AWildPokemon* EnemyPokemon = nullptr;
	class ACursor* Cursor = nullptr;
	USpriteRenderer* CursorRender = nullptr;
	
	USpriteRenderer* PlayerPokemonShadow = nullptr;
	USpriteRenderer* EnemyPokemonShadow = nullptr;
	
	USpriteRenderer* PlayerPokemonUI = nullptr;
	USpriteRenderer* EnemyPokemonUI = nullptr;

	USpriteRenderer* SelectMenu = nullptr;
	USpriteRenderer* BattleSelectMenu = nullptr;
	USpriteRenderer* BattleText = nullptr;

	FVector2D PlayerLocation = FVector2D::ZERO;
	
	FVector2D MosterBallLocation = FVector2D::ZERO;

	class APokemonBattleMap* BackImage;

	float ThrowingTime = 0.0f;
	float BallThrowTime = 2.5f;
	float SkillTextDelay = 2.0f;


	bool IsPlayerPokemonShadowMoved = false;
	bool IsEnemyPokemonShadowMoved = false;
	bool IsPlayerPokemonUIMoved = false;
	bool IsEnemyPokemonUIMoved = false;
	bool bEnemyPokemonPositioned = false;
	bool IsPlayerPokemonTextMoved = false;
	bool IsEnemyPokemonTextMoved = false;
	bool IsGoMessageDisplayed = false;
	bool bIsChatting = false;
	bool IsEnemyPokemonDead = false;
	bool IsEnemyPokemonDeadEventEnd = false;
	bool IsBackGroundSetting = false;
	bool IsThrowing = false;   
	bool IsChatOn = false;
	bool IsMenuOn = false;
	bool IsBattleNow = false;
	bool IsBattleCursorSet = false;
	bool IsPlayerTurn = true; 

	bool IsTextDisplayed = false;

	UTimeEvent TimeEventManager;

	class APokemonText* ChatText = nullptr;
	class APokemonText* BattleChatText = nullptr;
	
	class APokemonText* MyPokemonStat = nullptr;
	class APokemonText* MyPokemonLevelText = nullptr;
	class APokemonText* MyPokemonHPText = nullptr;
	class APokemonText* MyPokemonMaxHPText = nullptr;

	class APokemonText* MyPokemonSkill1 = nullptr;
	class APokemonText* MyPokemonSkill2 = nullptr;
	class APokemonText* MyPokemonSkill3 = nullptr;
	class APokemonText* MyPokemonSkill4 = nullptr;



	class APokemonText* EnemyPokemonStat = nullptr;
	class APokemonText* EnemyPokemonLevelText = nullptr;

	
	bool bHasSpawnedPokemon = false; 
	bool bHasDisplayedMenuText = false;

	class USoundPlayer BGMPlayer;

	float CurrentHPBarScale = 1.0f; 
	float TargetHPBarScale = 1.0f;  

	float CurrentEXPBarScale = 0.0f;
	float TargetEXPBarScale = 0.0f; 

	float AnimationSpeed = 2.0f; 

	int PokemonMapLevel = 0;
};

