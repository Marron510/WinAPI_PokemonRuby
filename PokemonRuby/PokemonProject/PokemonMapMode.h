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
	
protected:

private:
	class AFade* Fade = nullptr;
	class ATruck* NewTruck = nullptr;
	class APlayer* Player = nullptr;
	class AMother* Mother = nullptr;
	
	class APokemonMap* NewActor = nullptr;
	
	UTimeEvent TimeEventManager;

	FVector2D TileSize = FVector2D(96, 96);

	class APokemonText* ChatText;
	std::string enter = "\n";
	std::vector<std::string> Dialogues = 
	{
	"Mom: LADON, we are here, honey!",
	"Mom: It must be tiring riding with" + enter + "our things in the moving truck.",
	"Mom: Well, this is LITTLEROOT TOWN!",
	"Mom: How do you like it?" + enter + "This is our new home!",
	"Mom: It has a quaint feel,but it seems" + enter + "to be an easy place to live!",
	"Mom: And,you get your own room , LADON!" + enter + "LET's go inside."
	};

	int CurrentDialogueIndex = 0; 
};


