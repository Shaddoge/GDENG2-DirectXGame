#include "ColorPicker.h"

ColorPicker::ColorPicker() : UIScreen("ColorPicker", false)
{
}

ColorPicker::~ColorPicker()
{
}

void ColorPicker::DrawUI()
{
	ImGui::Begin("Color Picker", &isActive);
	ImGui::ColorPicker4(label.c_str(), col, colorEditFlag);
	ImGui::End();
}