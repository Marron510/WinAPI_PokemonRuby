#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>


HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasss;



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
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
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

    hInstance = _Instance;
}

int UEngineWindow::WindowMessageLoop()
{
    // 윈도우 창에서 사용하는 단축키는 사용하지 않음
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{

    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasss.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasss.find(std::string(_Class.lpszClassName));

    // ckw
    if (EndIter != FindIter)
    {
        // std::string ErrorText = "같은 이름의 윈도우 클래스를 2번 등록했습니다" + std::string(_Class.lpszClassName);

        // std::string 내부에 들고 있는 맴버변수 => std::string => std::vector<char>
        // std::vector<char> char* = new char[100];
        // ErrorText const char* 리턴해주는 함수가 c_str()
        // const char* Text = ErrorText.c_str();
        MSGASSERT("같은 이름의 윈도우 클래스를 2번 등록했습니다" + std::string(_Class.lpszClassName));
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasss.insert(std::pair{ _Class.lpszClassName, _Class });
}


UEngineWindow::UEngineWindow()
{
  
}

UEngineWindow::~UEngineWindow()
{

}

void UEngineWindow::Create(std::string_view _ClassName)
{
    Create("Window", _ClassName);
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasss.contains(_ClassName.data()))
    {
        MSGASSERT("등록하지 않은 클래스로 윈도우창을 만들려고 했습니다" + std::string(_ClassName));
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!WindowHandle)
    {
        MSGASSERT("윈도우 생성에 실패했습니다." + std::string(_TitleName));
        return;
    }

}

void UEngineWindow::Open(std::string_view _TitleName)
{
    if (nullptr == WindowHandle)
    {
        Create();
    }

    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
}