#include "MenuBar.h"

MenuBar::MenuBar() : UIScreen("MenuBar", true)
{
}

MenuBar::~MenuBar()
{
}

void MenuBar::DrawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Color Picker"))
            {
                UIManager::Get()->ToggleUI("COLOR_PICKER");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("Credits"))
            {
                
                UIManager::Get()->ToggleUI("CREDITS_SCREEN");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
