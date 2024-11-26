#pragma once
#include <EngineCore/Actor.h>

class APokemonMap : public AActor
{
public:
	// 持失切 社瑚切
	APokemonMap();
	~APokemonMap();

	// delete funcion

	APokemonMap(const APokemonMap& _Other) = delete;
	APokemonMap(APokemonMap&& _Other) noexcept = delete;
	APokemonMap& operator=(const APokemonMap& _Other) = delete;
	APokemonMap& operator=(APokemonMap&& _Other) noexcept = delete;

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

