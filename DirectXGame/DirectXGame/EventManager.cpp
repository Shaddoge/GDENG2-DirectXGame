#include "EventManager.h"

EventManager* EventManager::sharedInstance = NULL;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::Initialize()
{
	sharedInstance = new EventManager();
}

void EventManager::BindListener(String name, EventListener* listener)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		iterator->second.push_back(listener);
	}
	else
	{
		list<EventListener*> new_list;
		new_list.push_back(listener);
		sharedInstance->binded_events.insert(make_pair(name, new_list));
	}
}

void EventManager::UnbindListener(String name, EventListener* listener)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		iterator->second.remove(listener);
		if (iterator->second.size() <= 0)
		{
			sharedInstance->binded_events.erase(iterator);
		}
	}
}

void EventManager::Invoke(String name)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Receive(name);
		}
	}
}

void EventManager::Invoke(String name, bool value)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Receive(name, value);
		}
	}
}

void EventManager::Invoke(String name, String value)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Receive(name, value);
		}
	}
}

void EventManager::Invoke(String name, int value)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Receive(name, value);
		}
	}
}

void EventManager::Invoke(String name, float value)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Receive(name, value);
		}
	}
}

void EventManager::Invoke(String name, Vector2D value)
{
	map<String, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Receive(name, value);
		}
	}
}
