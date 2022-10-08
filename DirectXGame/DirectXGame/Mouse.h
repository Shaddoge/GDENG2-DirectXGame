#pragma once
#include "Window.h"
#include "EventManager.h"
#include <iostream>


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
	bool pos_setup = false;
	
	bool l_is_down = false;
	bool r_is_down = false;

	POINT old_pos = {0, 0};
	POINT curr_pos = {0, 0};
	POINT delta_pos = {0, 0};

	friend class Window;
};

