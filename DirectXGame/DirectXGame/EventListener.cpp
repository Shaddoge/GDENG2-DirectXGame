#include "EventListener.h"
#include <iostream>
EventListener::EventListener()
{
}

EventListener::~EventListener()
{
}

void EventListener::Invoke()
{
	std::cout << "Invoke!" << std::endl;
}

void EventListener::Invoke(bool value)
{
}

void EventListener::Invoke(int value)
{
}

void EventListener::Invoke(float value)
{
}

void EventListener::Invoke(vec2 value)
{
}