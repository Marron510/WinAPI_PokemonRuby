#pragma once

#include <EngineCore/Actor.h>


class ACursor : public AActor
{
public:
	enum class ECursorState
	{
		Menu,
		Battle,
		SelectPokemon,
		Bag
	};


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

	FVector2D* GetCursorPositionsForState(ECursorState State);



	USpriteRenderer* GetCursorRender()
	{
		return CursorRender;
	}

protected:

private:
	const float CursorPosMax = 1000.0f;
	class USpriteRenderer* CursorRender = nullptr;

	FVector2D MenuCursorPositions[4] =
	{
		FVector2D(740, 640), 
		FVector2D(1030, 640),
		FVector2D(740, 720), 
		FVector2D(1030, 720) 
	};

	FVector2D BattleCursorPositions[4] = 
	{
		FVector2D(740, 640), 
		FVector2D(1030, 640),
		FVector2D(740, 720), 
		FVector2D(1030, 720) 
	};

	FVector2D SelectPokemonCursorPositions[4] = 
	{
		FVector2D(740, 640), 
		FVector2D(1030, 640),
		FVector2D(740, 720), 
		FVector2D(1030, 720) 
	};

	FVector2D BagCursorPositions[4] = 
	{
		FVector2D(740, 640), 
		FVector2D(1030, 640),
		FVector2D(740, 720), 
		FVector2D(1030, 720) 
	};

};

