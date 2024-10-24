#include "PreCompile.h"

#include <ContentsProject/PokemonCore.h>
#include <EngineCore/EngineAPICore.h>


#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsProject.lib")
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	PokemonCore Pokemon;
	return UEngineAPICore::EngineStart(hInstance, &Pokemon);
}