#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include "PokemonText.h"
#include "PokemonMath.h"
#include "Player.h"

class ALaborProfessorBirchMode : public AGameMode
{
public:
	static FIntPoint LaborProfessorBirchModeChangePos;
	static APlayer::EPlayerDir ALaborProfessorBirchModePlayerDir;

	// 持失切 社瑚切
	ALaborProfessorBirchMode();
	~ALaborProfessorBirchMode();

	// delete funcion

	ALaborProfessorBirchMode(const ALaborProfessorBirchMode& _Other) = delete;
	ALaborProfessorBirchMode(ALaborProfessorBirchMode&& _Other) noexcept = delete;
	ALaborProfessorBirchMode& operator=(const ALaborProfessorBirchMode& _Other) = delete;
	ALaborProfessorBirchMode& operator=(ALaborProfessorBirchMode&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	void LevelChange(float _DeltaTime);

	void LevelChangeStart() override;
	void StartProfessorDialogue();
	void DisplayNextDialogue(); 
	void RenderChatAbovePlayer();


protected:

private:
	class APlayer* Player = nullptr;
	class AProfessor* Professor = nullptr;
	class AFade* Fade = nullptr;
	FVector2D TileSize = FVector2D(96, 96);

	class USoundPlayer BGMPlayer;

	class APokemonText* ChatText; 
	std::string enter = "\n"; 
	std::vector<std::string> Dialogues =
	{
		"Professor: Whew! I was in the tall grass" + enter + "studying wild Pokemon when I was jumped!",
		"Professor: You saved me.Thanks a lot!",
		"Professor: Oh? Hi! You're BRENDAN!" + enter + "I've heard about you from your father.",
		"Professor: I've heard that you don't have" + enter +"your own POKEMON yet.",
		"Professor: But the way you battled earlier," + enter + "you pulled it off with aplomb!",
		"Professor: I guess you have your father's " + enter +  "blood in your veins after all!",
		"Professor: Oh yes.As thanks for rescuing me" + enter + "I'd like you to have the POKEMON you used.",
		"Professor: If you work at becoming a strong " + enter +  "trainer,here's what I think you'll do.",
		"Professor: My kid, May, is also studying" + enter + "Pokemon while helping me out.",
		"Professor: Don't you think it might be a " + enter + "good idea to go see May?",
		"Professor: Great! May should be happy, too",
		"Professor: Go and have a wonderful" + enter + "adventure together!"
	};

	int CurrentDialogueIndex = 0;

};

