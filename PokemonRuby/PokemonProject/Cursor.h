#pragma once

#include <EngineCore/Actor.h>


class ACursor : public AActor
{
public:

	// 持失切 社瑚切
	ACursor();
	~ACursor();

	// delete funcion

	ACursor(const ACursor& _Other) = delete;
	ACursor(ACursor&& _Other) noexcept = delete;
	ACursor& operator=(const ACursor& _Other) = delete;
	ACursor& operator=(ACursor&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* GetCursorRender()
	{
		return CursorRender;
	}

protected:

private:
	const float CursorPosMax = 1000.0f;
	class USpriteRenderer* CursorRender = nullptr;
};

