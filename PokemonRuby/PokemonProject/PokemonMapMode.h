#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"


class APokemonMapMode : public AGameMode
{
public:
	static FIntPoint PokemonMapModeChangePos;
	static APlayer::EPlayerDir PokemonMapModePlayerDir;

	// 持失切 社瑚切
	APokemonMapMode();
	~APokemonMapMode();

	// delete funcion

	APokemonMapMode(const APokemonMapMode& _Other) = delete;
	APokemonMapMode(APokemonMapMode&& _Other) noexcept = delete;
	APokemonMapMode& operator=(const APokemonMapMode& _Other) = delete;
	APokemonMapMode& operator=(APokemonMapMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void LevelChange();

	void LevelChangeStart() override;
	void RenderChatAbovePlayer();
	void DisplayNextDialogue();

	void MoveToHouse();
	void ChildInteractionEvent();
	void ProfessorInteractionEvent();
	void ProfessorHelpEvent();
	void BagInteractionEvent();


protected:

private:
	class AFade* Fade = nullptr;
	class ATruck* NewTruck = nullptr;
	class APlayer* Player = nullptr;
	class AMother* Mother = nullptr;
	class AChild* Child = nullptr;
	class AProfessor* Professor = nullptr;
	class AMonster* Monster = nullptr;
	class ABag* Bag = nullptr;
	class APokemonMap* NewActor = nullptr;
	
	bool bIsDialogueActive = false;
	bool bIsChildDialogue = false;

	UTimeEvent TimeEventManager;

	FVector2D TileSize = FVector2D(96, 96);

	class APokemonText* ChatText;
	std::string enter = "\n";
	std::vector<std::string> Dialogues = 
	{
	"Mom: BRENDAN, we are here, honey!",
	"Mom: It must be tiring riding with" + enter + "our things in the moving truck.",
	"Mom: Well, this is LITTLEROOT TOWN!",
	"Mom: How do you like it?" + enter + "This is our new home!",
	"Mom: It has a quaint feel,but it seems" + enter + "to be an easy place to live!",
	"Mom: And,you get your own room , LADON!" + enter + "Let's go inside."
	};

	std::vector<std::string> Dialogues1 =
	{
	"I can hear someone shouting" + enter + "down the road here",
	"What should I do?What should we do?" + enter + "Somebody has to go help...",
	};

	std::vector<std::string> Dialogues2 =
	{
	"H..help me!",
	"Hello!You over there!" + enter + "Please!Help!",
	"In my BAG!" + enter + "there's a POKEBALL!",
	};
	int CurrentDialogueIndex = 0; 
	int CurrentDialogue1Index = 0;
	int CurrentDialogue2Index = 0;

	bool bIsProfessorDialogue = false;

	bool bMotherDialogueCompleted = false;
	bool bChildDialogueCompleted = false; 
	bool bProfessorDialogueCompleted = false;
};


