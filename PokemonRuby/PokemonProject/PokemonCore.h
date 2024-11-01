#pragma once
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>


class PokemonCore : public UContentsCore
{
public:
	// 持失切 社瑚切
	PokemonCore();
	~PokemonCore();

	// delete funcion

	PokemonCore(const PokemonCore& _Other) = delete;
	PokemonCore(PokemonCore&& _Other) noexcept = delete;
	PokemonCore& operator=(const PokemonCore& _Other) = delete;
	PokemonCore& operator=(PokemonCore&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel;
	ULevel* LittleRootTownLevel;
};

