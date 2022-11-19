#pragma once
#include <string>
#include "Vector2D.h"
#include "Vector3.h"

class EventListener
{
public:
	typedef std::string String;
public:
	EventListener();
	~EventListener();
	virtual void Receive(String event_name);
	virtual void Receive(String event_name, bool value);
	virtual void Receive(String event_name, String String_name);
	virtual void Receive(String event_name, int value);
	virtual void Receive(String event_name, float value);
	virtual void Receive(String event_name, Vector2D value);
};