#include "Window.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

Window* window = nullptr;

Window::Window()
{
}

// ImGui Input Handler

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
    {
        Vector2D new_size = Vector2D(window->GetClientWindowRect().right - window->GetClientWindowRect().left, window->GetClientWindowRect().bottom - window->GetClientWindowRect().top);
        window->OnResize(new_size.x, new_size.y);
        break;
    }
    // MOUSE
    case WM_RBUTTONDOWN:
    {
        Mouse::SetDown(MouseInputType::R, true);
        window->OnRMouseDown();
        break;
    }
    case WM_RBUTTONUP:
    {
        Mouse::SetDown(MouseInputType::R, false);
        window->OnRMouseUp();
        break;
    }
    case WM_LBUTTONDOWN:
    {   
        Mouse::SetDown(MouseInputType::L, true);
        window->OnLMouseDown();
        break;
    }
    case WM_LBUTTONUP:
    {
        Mouse::SetDown(MouseInputType::L, false);
        window->OnLMouseUp();
        break;
    }
    case WM_MOUSEMOVE: {
        //                x               y
        POINT new_pos = { LOWORD(lparam), HIWORD(lparam) };
        Mouse::OnDrag(new_pos);
        
        if (Mouse::GetIsDown(MouseInputType::L))
        {                   
            window->OnLMouseDrag(Mouse::GetDeltaPos());
        }
        else if (Mouse::GetIsDown(MouseInputType::R))
        {
            window->OnRMouseDrag(Mouse::GetDeltaPos());
        }
        break;
    }
    // Keyboard
    case WM_KEYUP: {
        char key = char(wparam);
        if (key != NULL)
        {
            window->OnKeyUp(key);
        }
        
        break;
    }
    case WM_KEYDOWN: {
        char key = char(wparam);
        if (key != NULL)
        {
            window->OnKeyDown(key);
        }

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
    wc.lpszClassName = "MyWindowClass";
    wc.lpszMenuName = "";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc ;

    // If registration of class fails.
    if(!::RegisterClassEx(&wc))
        return false;

    if (!window)
        window = this;

    // Window creation
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        1600, 900, NULL, NULL, NULL, this);
    
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

void Window::OnResize(int width, int height)
{
}

void Window::OnLMouseDown()
{
}

void Window::OnRMouseDown()
{
}

void Window::OnLMouseUp()
{
}

void Window::OnRMouseUp()
{
}

void Window::OnLMouseDrag(Vector2D delta_pos)
{
}

void Window::OnRMouseDrag(Vector2D delta_pos)
{
}

void Window::OnKeyDown(const char key)
{
}

void Window::OnKeyUp(const char key)
{
}

Window::~Window()
{
}