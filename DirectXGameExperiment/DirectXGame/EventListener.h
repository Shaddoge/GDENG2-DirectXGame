#pragma once
#include <string>
#include "Vector2.h"
#include "Vector3.h"

using namespace std;

class EventListener
{
public:
	EventListener();
	~EventListener();
	virtual void Receive(string event_name);
	virtual void Receive(string event_name, bool value);
	virtual void Receive(string event_name, int value);
	virtual void Receive(string event_name, float value);
	virtual void Receive(string event_name, Vector2 value);
};