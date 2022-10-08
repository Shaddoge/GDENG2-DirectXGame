#pragma once
#include <string>
#include "Structs.h"

class EventListener
{
public:
	EventListener();
	~EventListener();

	virtual void Invoke();
	virtual void Invoke(bool value);
	virtual void Invoke(int value);
	virtual void Invoke(float value);
	virtual void Invoke(vec2 value);
};