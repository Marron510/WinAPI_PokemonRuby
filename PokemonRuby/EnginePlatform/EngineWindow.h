#pragma once
#include <Windows.h>


#include <map>
#include <string>
#include <functional>


#include <EngineBase/EngineDelegate.h>


class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;
	
	void Create(std::string_view _TitleName , std::string_view _ClassName = "Default");
	//std::string은 new를 하기 때문에 최적화를 위해 string_view를 사용하지만
	//std::string과 달리 std::string_view 는 수정을 하지 못한다는 단점이 있다.
	void Open(std::string_view _TitleName = "Window");

	inline HDC GetBackBuffer()
	{
		return BackBuffer;
	}

protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasses;
	HDC BackBuffer = nullptr;
	HWND WindowHandle = nullptr;
};