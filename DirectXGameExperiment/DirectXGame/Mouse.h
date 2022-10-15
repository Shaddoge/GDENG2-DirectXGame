#pragma once
#include <iostream>
#include "EventManager.h"
#include "Window.h"
#include "Vector2.h"

using namespace std;

enum MouseInputType
{
	L = 0,
	R
};

class Window;

class Mouse
{
public:
	static void Initialize();
// Get
public:
	static POINT GetPos();
	static Vector2 GetDeltaPos();
	static bool GetIsDown( MouseInputType type );
// Set
public:
	static void SetDown(MouseInputType type, bool is_down);
// Event
public:
	static void OnDrag(POINT new_pos);
private:
	static Mouse* sharedInstance;
private:
	Mouse();
	~Mouse();
private:
	bool l_released = true;
	bool l_is_down = false;
	bool r_is_down = false;

	POINT old_pos = {0, 0};
	POINT curr_pos = {0, 0};
	Vector2 delta_pos = {0, 0};

	friend class Window;
};