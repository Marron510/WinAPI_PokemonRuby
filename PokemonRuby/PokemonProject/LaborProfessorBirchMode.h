#pragma once
#include <EngineCore/GameMode.h>
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

protected:

private:
	class APlayer* Player = nullptr;
	class AProfessor* Professor = nullptr;
	class AFade* Fade = nullptr;
	FVector2D TileSize = FVector2D(96, 96);
};

