#pragma once
#include "UIScreen.h"
class ColorPicker : public UIScreen
{
public:
	ColorPicker();
	~ColorPicker();
	void DrawUI() override;

private:
	String label = "Color";
	float col[3] = {0, 0, 0};
	ImGuiColorEditFlags colorEditFlag = ImGuiColorEditFlags_PickerHueWheel;
};

