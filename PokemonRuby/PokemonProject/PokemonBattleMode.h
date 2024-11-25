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


	std::string MyPokemonName;
	std::string enter = "\n";
	std::string MyPokemonSkillText;
	std::string EnemyPokemonSkillText;


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
	bool IsPlayerPokemonTextMoved = false;
	bool IsEnemyPokemonTextMoved = false;
	bool IsGoMessageDisplayed = false;

	bool IsBackGroundSetting = false;
	bool IsThrowing = false;   
	bool IsChatOn = false;
	bool IsMenuOn = false;
	bool IsBattleNow = false;
	bool IsBattleCursorSet = false;
	bool IsPlayerTurn = true;  // 플레이어 턴이면 true, 상대 턴이면 false

	bool IsTextDisplayed = false;

	UTimeEvent TimeEventManager;

	/*bool HasUsedSkill1 = false;
	bool HasUsedSkill2 = false;
	bool HasUsedSkill3 = false;
	bool HasUsedSkill4 = false;*/

	class APokemonText* ChatText = nullptr;
	class APokemonText* BattleChatText = nullptr;
	class APokemonText* MyPokemonStat = nullptr;
	class APokemonText* MyPokemonSkill1 = nullptr;
	class APokemonText* MyPokemonSkill2 = nullptr;
	class APokemonText* MyPokemonSkill3 = nullptr;
	class APokemonText* MyPokemonSkill4 = nullptr;



	class APokemonText* EnemyPokemonStat = nullptr;
		
	bool bHasDisplayedMenuText = false;
	int PokemonMapLevel = 2;
};

