#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Window.h"
#include "UIScreen.h"
#include "GraphicsEngine.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "DeviceContext.h"
#include "MenuBar.h"
#include "CreditsScreen.h"
#include "EventListener.h"

class UINames {
public:
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String MENU_BAR = "MENU_BAR";
	const String COLOR_PICKER = "COLOR_PICKER";
};

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<UIScreen*> UIList;
	typedef std::unordered_map<String, UIScreen*> UITable;

	static UIManager* Get();
	static void Initialize(HWND hwnd);
	static void Destroy();
	
	void ToggleUI(String name);
	void DrawAllUI();

	static const int WINDOW_WIDTH = 1600;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};

