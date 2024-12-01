#pragma once
#include <EngineCore/Actor.h>

class ALaborProfessorBirchMap : public AActor
{
public:
	// 持失切 社瑚切
	ALaborProfessorBirchMap();
	~ALaborProfessorBirchMap();

	// delete funcion

	ALaborProfessorBirchMap(const ALaborProfessorBirchMap& _Other) = delete;
	ALaborProfessorBirchMap(ALaborProfessorBirchMap&& _Other) noexcept = delete;
	ALaborProfessorBirchMap& operator=(const ALaborProfessorBirchMap& _Other) = delete;
	ALaborProfessorBirchMap& operator=(ALaborProfessorBirchMap&& _Other) noexcept = delete;
	
	USpriteRenderer* GetCurMap()
	{
		return SpriteRenderer;
	}

	USpriteRenderer* GetChatRender()
	{
		return ChatRenderer;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer;
	USpriteRenderer* ChatRenderer;
};

