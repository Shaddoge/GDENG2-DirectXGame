#include "ColorPicker.h"

ColorPicker::ColorPicker() : UIScreen("ColorPicker", false)
{
	//EventManager::BindListener("ColorPicker", this);
}

ColorPicker::~ColorPicker()
{
	//EventManager::UnbindListener("ColorPicker", this);
}

void ColorPicker::DrawUI()
{
	ImGui::Begin("Color Picker", &isActive);
	ImGui::ColorPicker4(label.c_str(), col, colorEditFlag);
	ImGui::End();
}