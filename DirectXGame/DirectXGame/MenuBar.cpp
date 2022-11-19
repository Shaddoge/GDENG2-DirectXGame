#include "MenuBar.h"
#include "GameObjectManager.h"

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
        if (ImGui::BeginMenu("GameObject"))
        {
            if (ImGui::MenuItem("Cube"))
            {
                GameObjectManager::GetInstance()->CreateObject(GameObject::PrimitiveType::CUBE);
            }
            if (ImGui::MenuItem("Physics Cube"))
            {
                for (int i = 0; i < 20; i++)
                {
                    GameObjectManager::GetInstance()->CreateObject(GameObject::PrimitiveType::PHYSICS_CUBE);

                }
            }
            if (ImGui::MenuItem("Plane"))
            {
                GameObjectManager::GetInstance()->CreateObject(GameObject::PrimitiveType::PLANE);
            }
            if (ImGui::MenuItem("Physics Plane"))
            {
                GameObjectManager::GetInstance()->CreateObject(GameObject::PrimitiveType::PHYSICS_PLANE);
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
