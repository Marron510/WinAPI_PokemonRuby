#include "PreCompile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>


HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;
int WindowCount = 0;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        --WindowCount;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    hInstance = _Instance;

    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;
    CreateWindowClass(wcex);

    
}

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction) // 함수포인터로 윈도우 창에서 여러 기능들이 작동하게 만듬
{
    // 윈도우 창에서 사용하는 단축키는 사용하지 않음
    MSG msg = MSG();

    if (true == _StartFunction.IsBind()) // 엔진이 beginplay 하지 않았다면 실행
    {
        _StartFunction();
    }

    while (0 != WindowCount)
    {
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 메세지가 있을때만 일정 프레임 내에 처리하고 나머지 메세지는 삭제
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (true == _FrameFunction.IsBind()) // 현재 작동하는 함수(움직임)가 없다면 실행
        {
            _FrameFunction();
        }
    }

    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{

    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasses.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasses.find(std::string(_Class.lpszClassName));

    if (EndIter != FindIter)
    {
        MSGASSERT(std::string(_Class.lpszClassName) + " 같은 이름의 윈도우 클래스를 2번 등록했습니다");
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasses.insert(std::pair{ _Class.lpszClassName, _Class }); // map으로 윈도우 classes를 구현
}


UEngineWindow::UEngineWindow()
{
  
}

UEngineWindow::~UEngineWindow()
{

}


void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasses.contains(_ClassName.data()))
    {
        MSGASSERT(std::string(_ClassName) + " 등록하지 않은 클래스로 윈도우창을 만들려고 했습니다");
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (nullptr == WindowHandle)
    {
        MSGASSERT(std::string(_TitleName) + " 윈도우 생성에 실패했습니다.");
        return;
    }

    BackBuffer = GetDC(WindowHandle);
}

void UEngineWindow::Open(std::string_view _TitleName)
{
    if (0 == WindowHandle)
    {
        Create("Pokemon Ruby");
    }

    if (0 == WindowHandle)
    {
        return;
    }

    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount; // 윈도우 창의 개수 추가
}