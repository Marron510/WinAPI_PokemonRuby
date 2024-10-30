#include "PreCompile.h"

#include <PokemonProject/PokemonCore.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineTimer.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "PokemonProject.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	PokemonCore Pokemon;
	return UEngineAPICore::EngineStart(hInstance, &Pokemon);
}