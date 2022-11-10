#include "UIManager.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::Get()
{
	return sharedInstance;
}

void UIManager::Initialize(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);
}

void UIManager::Destroy()
{
}

void UIManager::ToggleUI(String name)
{
	if (this->uiTable[name] != nullptr)
	{
		bool isActive = this->uiTable[name]->GetActive();
		this->uiTable[name]->SetActive(!isActive);
	}
}

void UIManager::DrawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++)
	{
		this->uiList[i]->Update();
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND hwnd)
{
	// Initialize
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)(io);

	// Style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::Get()->GetDirectXDevice(), GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext());

	// Populate UI Table
	UINames uiNames;
	MenuBar* menuBar = new MenuBar();
	this->uiTable[uiNames.MENU_BAR] = menuBar;
	this->uiList.push_back(menuBar);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ColorPicker* colorPicker = new ColorPicker();
	this->uiTable[uiNames.COLOR_PICKER] = colorPicker;
	this->uiList.push_back(colorPicker);
}

UIManager::~UIManager()
{
	//EventManager::UnbindListener("ToggleCreditsScreen", );
}
