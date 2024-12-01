#pragma once
#include <EngineCore/Actor.h>
#include "PokemonEnum.h"

class AChild : public AActor
{
public:
	enum class ENPCDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};


	// 持失切 社瑚切
	AChild();
	~AChild();

	// delete funcion

	AChild(const AChild& _Other) = delete;
	AChild(AChild&& _Other) noexcept = delete;
	AChild& operator=(const AChild& _Other) = delete;
	AChild& operator=(AChild&& _Other) noexcept = delete;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetLookDirection(ENPCDirection Direction);

	class USpriteRenderer* GetRender()
	{
		return SpriteRenderer;
	}

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	ENPCDirection CurrentDirection = ENPCDirection::NONE;
};

