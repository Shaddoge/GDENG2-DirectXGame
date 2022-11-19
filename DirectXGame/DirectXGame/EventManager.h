#pragma once

#include <iostream>
#include <list>
#include <map>
#include "EventListener.h"
#include "Vector2D.h"
#include <string>

class EventManager
{
public:
	typedef std::string String;
public:
	EventManager();
	~EventManager();
public:
	static void Initialize();
	static void BindListener(String name, EventListener* event);
	static void UnbindListener(String name, EventListener* event);
	static void Invoke(String name);
	static void Invoke(String name, bool value);
	static void Invoke(String name, String value);
	static void Invoke(String name, int value);
	static void Invoke(String name, float value);
	static void Invoke(String name, Vector2D value);
private:
	static EventManager* sharedInstance;
	
private:
	map<String, list<EventListener*>> binded_events;
};