#include "CreditsScreen.h"

CreditsScreen::CreditsScreen() : UIScreen("CreditsScreen", false)
{
	//EventManager::BindListener("ToggleCreditsScreen", this);
}

CreditsScreen::~CreditsScreen()
{
	//EventManager::UnbindListener("ToggleCreditsScreen", this);
}

void CreditsScreen::DrawUI()
{
	String filename = "Image/DLSU.png";
	int imgWidth = 0;
	int imgHeight = 0;
	ID3D11ShaderResourceView* texture = NULL;
	bool ret = LoadTextureFromFile(filename.c_str(), &texture, &imgWidth, &imgHeight);
	IM_ASSERT(ret);

	ImGui::Begin("Credits", &isActive);
	if (ret)
	{
		ImGui::Image((void*)texture, ImVec2(256, 256));
	}
	ImGui::Text("About\n\n");
	ImGui::Text("Scene Editor v0.01");
	ImGui::Text("Developed by: John Adriel Santos\n\n");
	ImGui::Text("Acknowledgements: ");
	ImGui::Text("PardCode Game Engine Tutorial");
	ImGui::Text("Sir Neil's GDENG2 Course");
	ImGui::End();
}
