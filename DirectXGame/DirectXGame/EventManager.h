#pragma once

#include <iostream>
#include <list>
#include <map>
#include "EventListener.h"

using namespace std;

class EventManager
{
public:
	EventManager();
	~EventManager();
public:
	static void Initialize();
	static void BindEvent(string name, EventListener* event);
	static void UnbindEvent(string name, EventListener* event);
	static void Invoke(string name);
	static void Invoke(string name, bool value);
	static void Invoke(string name, int value);
	static void Invoke(string name, float value);
	static void Invoke(string name, vec2 value);
private:
	static EventManager* sharedInstance;
private:
	map<string, list<EventListener*>> binded_events;
};