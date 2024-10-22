#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EnginePlatform.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// UGameEngine::Start(hInstance); <= 추후 아래 내용 랩핑을 통해 바꿀것임
	UEngineWindow::EngineWindowInit(hInstance);
	UEngineWindow NewWindow;
	NewWindow.Open();
	return UEngineWindow::WindowMessageLoop();
}