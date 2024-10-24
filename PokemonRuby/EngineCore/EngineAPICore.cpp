#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;


UEngineAPICore::UEngineAPICore()
{
	MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	UserCore = _UserCore;
	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();


	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));;
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);

}

void UEngineAPICore::EngineBeginPlay() // 유저코어 실행
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick() // 엔진실행
{
	UserCore->Tick();
	MainCore->Tick();
}
void UEngineAPICore::Tick()
{

}

