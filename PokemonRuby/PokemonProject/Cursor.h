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
		ABag
	};

	FVector2D MenuCursorPositions[4] =
	{
		FVector2D(740, 640),//lefttop
		FVector2D(1030, 640), //righttop
		FVector2D(740, 720),//leftbottom
		FVector2D(1030, 720)//rightbottom
	};

	FVector2D BattleCursorPositions[4] = 
	{
		FVector2D(50, 640), //lefttop
		FVector2D(450, 640), //righttop
		FVector2D(50, 720), //leftbottom
		FVector2D(450, 720) //rightbottom
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
	void SetState(ECursorState NewState);
	void SetBattleModeInstance(class APokemonBattleMode* BattleMode);

	USpriteRenderer* GetCursorRender()
	{
		return CursorRender;
	}

	ECursorState GetCurrentCursorState()
	{
		return CurrentState;
	}

	FVector2D GetBattleCursorPosition(int Index)
	{
		if (Index >= 0 && Index < 4)
		{
			return BattleCursorPositions[Index];
		}
		else
		{
			return FVector2D(0, 0);
		}
	}

	FVector2D GetMenuCursorPosition(int Index)
	{
		if (Index >= 0 && Index < 4)
		{
			return MenuCursorPositions[Index];
		}
		else
		{
			return FVector2D(0, 0);
		}
	}


protected:

private:
	const float CursorPosMax = 1000.0f;
	class USpriteRenderer* CursorRender = nullptr;
	ECursorState CurrentState = ECursorState::Menu;
	class AMyPokemon* Mypokemon = nullptr;
	class APokemonBattleMode* BattleModeInstance = nullptr;
	bool IsFirstMenuZPressIgnored = true;
	bool IsFirstBattleZPressIgnored = true;

	class APokemonText* ChatText = nullptr;
};

