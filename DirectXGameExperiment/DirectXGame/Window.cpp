#include "Window.h"

Window* window = nullptr;

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    // MOUSE
    case WM_LBUTTONDOWN:
    {   
        Mouse::SetDown(MouseInputType::L, true);
        break;
    }
    case WM_LBUTTONUP:
    {
        Mouse::SetDown(MouseInputType::L, false);
        break;
    }
    case WM_MOUSEMOVE: {
        if (Mouse::GetIsDown(MouseInputType::L))
        {                   //x               y
            POINT new_pos = { LOWORD(lparam), HIWORD(lparam) };
            Mouse::OnDrag(new_pos);
            window->OnMouseDrag(Mouse::GetDeltaPos());
        }
        break;
    }
    // Keyboard
    case WM_CHAR: {
        char key = char(wparam);
        if (key != NULL)
            window->OnKeyDown(key);
        break;
    }

    case WM_CREATE:
    {
        // Create Event
        Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;

        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        window->SetHWND(hwnd);
        window->OnCreate();
        break;
    }
    case WM_DESTROY:
    {
        // Destroy Event
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

        window->OnDestroy();
        ::PostQuitMessage(0);
        break;
    }
    default:
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return NULL;
}
bool Window::Init()
{
    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc ;

    // If registration of class fails.
    if(!::RegisterClassEx(&wc))
        return false;

    if (!window)
        window = this;

    // Window creation
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        1024, 768, NULL, NULL, NULL, this);
    
    // If creation fails
    if (!m_hwnd)
        return false;
    
    // Show window
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    // Indicate window running
    m_is_run = true;

    return true;
}

bool Window::Broadcast()
{
    EngineTime::LogFrameStart();
    this->OnUpdate();
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Sleep(1);
    EngineTime::LogFrameEnd();
    return true;
}

bool Window::Release()
{
    // Destroy window
    if (!::DestroyWindow(m_hwnd))
        return false;

    return true;
}

bool Window::IsRun()
{
    return m_is_run;
}

RECT Window::GetClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);
    return rc;
}

void Window::SetHWND(HWND hwnd)
{
    this->m_hwnd = hwnd;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
    m_is_run = false;
}

void Window::OnMouseDrag(const Vector2 delta_pos)
{
}

void Window::OnKeyDown(const char key)
{
}

Window::~Window()
{
}