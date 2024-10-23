#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;


UEngineAPICore::UEngineAPICore()
{
	MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst)
{
	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core;
	Core.EngineMainWindow.Open();


	EngineDelegate NewDel;
	NewDel = EngineLoop; // 델리게이트에 한가지 기능만 넣었음
	return UEngineWindow::WindowMessageLoop(NewDel);

}

void UEngineAPICore::EngineLoop() // 엔진실행
{
	MainCore->Tick();
	MainCore->Render();
}

void UEngineAPICore::Tick()
{

}

void UEngineAPICore::Render()
{

}