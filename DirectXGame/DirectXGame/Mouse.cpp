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

Vector2 Mouse::GetDeltaPos()
{
	return sharedInstance->delta_pos;
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
		case L: {
			EventManager::Invoke("MouseLDown", is_down);
			sharedInstance->l_is_down = is_down; 
			if (!is_down)
			{
				sharedInstance->l_released = true;
			}
			break;
		}
		case R: {
			EventManager::Invoke("MouseRDown", is_down);
			sharedInstance->r_is_down = is_down; break;
			if (!is_down)
			{
				sharedInstance->r_released = true;
			}
		}
		default: break;
	}
}

void Mouse::OnDrag(POINT new_pos)
{
	if (sharedInstance->l_released)
	{
		sharedInstance->old_pos = { new_pos.x, new_pos.y };
		sharedInstance->l_released = false;
		return;
	}
	sharedInstance->curr_pos = new_pos;
	int old_pos_x = sharedInstance->old_pos.x;
	int old_pos_y = sharedInstance->old_pos.y;
	sharedInstance->delta_pos = Vector2(-(old_pos_x - new_pos.x), old_pos_y - new_pos.y );
	sharedInstance->old_pos = { new_pos.x, new_pos.y };
	EventManager::Invoke("MouseMove", sharedInstance->delta_pos);
}

Mouse::Mouse()
{
}	

Mouse::~Mouse()
{
}
