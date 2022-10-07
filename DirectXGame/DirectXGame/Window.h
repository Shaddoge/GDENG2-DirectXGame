#pragma once
#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	Window();
	// Initialize the window
	bool Init();
	bool Broadcast();
	// Release the window
	bool Release();
	bool IsRun();

	RECT GetClientWindowRect();
	void SetHWND(HWND hwnd);

	//EVENTS
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

