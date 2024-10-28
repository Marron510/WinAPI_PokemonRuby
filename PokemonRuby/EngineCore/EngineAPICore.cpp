#include "PreCompile.h"
#include "EngineAPICore.h"
#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;


UEngineAPICore::UEngineAPICore()
{
	MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
	std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Levels.clear();
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
	//UserCore->Tick();
	MainCore->Tick();
}
void UEngineAPICore::Tick()
{
	// 현재시간 재는법
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();

	// 키체크
	UEngineInput::GetInst().KeyCheck(DeltaTime);

	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진 코어에 현재 레벨이 지정되지 않았습니다");
		return;
	}

	UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->Render();
}


void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data(); // 입력한 이름으로 레벨이름 설정

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter) // 찾기 실행
	{
		MSGASSERT(ChangeName + "라는 이름의 레벨은 존재하지 않습니다.");
		return;
	}

	CurLevel = FindIter->second; // 찾았으면 현재 레벨로 설정
}