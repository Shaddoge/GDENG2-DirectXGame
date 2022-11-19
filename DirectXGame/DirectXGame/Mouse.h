#pragma once
#include <iostream>
#include "Window.h"
#include "Vector2D.h"

enum class MouseInputType
{
	L,
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
	static Vector2D GetDeltaPos();
	static bool GetIsDown( const MouseInputType& type );
// Set
public:
	static void SetDown(const MouseInputType& type, bool is_down);
	static void SetCursorPos(const POINT& pos);
	static void ShowCursor(bool shown);
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
	bool r_released = true;
	bool r_is_down = false;

	POINT old_pos = {0, 0};
	POINT curr_pos = {0, 0};
	Vector2D delta_pos = {0, 0};

	friend class Window;
};