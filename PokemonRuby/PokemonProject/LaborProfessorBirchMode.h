#pragma once
#include <EngineCore/GameMode.h>

class ALaborProfessorBirchMode : public AGameMode
{
public:
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

protected:

private:

};

