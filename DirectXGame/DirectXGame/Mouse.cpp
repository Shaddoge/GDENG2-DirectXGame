#include "Mouse.h"

Mouse* Mouse::sharedInstance = NULL;

void Mouse::Initialize()
{
	sharedInstance = new Mouse();
}

POINT Mouse::GetPos()
{
	//::GetCursorPos(&sharedInstance->mouse_pos);
	return sharedInstance->curr_pos;
}

bool Mouse::GetIsDown(MouseInputType type)
{
	switch (type)
	{
		case L: //std::cout << "Get L" << std::endl; 
				return sharedInstance->l_is_down; break;
		case R: //std::cout << "Get R" << std::endl; 
				return sharedInstance->r_is_down; break;
		default: return false;
	}
}

void Mouse::SetDown(MouseInputType type, bool is_down)
{

	switch (type)
	{
		case L: std::cout << "Set L" << std::endl;
				sharedInstance->l_is_down = is_down; break;
		case R: std::cout << "Set R" << std::endl; 
				sharedInstance->r_is_down = is_down; break;
		default: break;
	}
}

void Mouse::OnDrag(POINT new_pos)
{
	if (!sharedInstance->pos_setup)
	{
		sharedInstance->old_pos = { new_pos.x, new_pos.y };
		sharedInstance->pos_setup = true;
		return;
	}
	sharedInstance->curr_pos = new_pos;
	int old_pos_x = sharedInstance->old_pos.x;
	int old_pos_y = sharedInstance->old_pos.y;
	sharedInstance->delta_pos = { -(old_pos_x - new_pos.x), old_pos_y - new_pos.y };
	sharedInstance->old_pos = { new_pos.x, new_pos.y };
	
	vec2 vec2_pos = { sharedInstance->delta_pos.x, sharedInstance->delta_pos.y };
	EventManager::Invoke("Mouse", vec2_pos);
}

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}
