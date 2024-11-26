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
	
	
protected:

private:
	class AFade* Fade = nullptr;
	class ATruck* NewTruck = nullptr;
	class APlayer* Player = nullptr;
	class AMother* Mother = nullptr;
	
	class APokemonMap* NewActor = nullptr;
	
	UTimeEvent TimeEventManager;

	class APokemonText* ChatText = nullptr;
	
	FVector2D TileSize = FVector2D(96, 96);
};


