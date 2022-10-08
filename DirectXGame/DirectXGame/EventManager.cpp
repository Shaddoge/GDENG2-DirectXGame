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

void EventManager::BindEvent(string name, EventListener* listener)
{
	map<string, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
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
	//sharedInstance->binded_listener.push_back(listener);
	//cout << sharedInstance->binded_listener.size() << endl;
}

void EventManager::UnbindEvent(string name, EventListener* listener)
{
	map<string, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		iterator->second.remove(listener);
		if (iterator->second.size() <= 0)
		{
			sharedInstance->binded_events.erase(iterator);
		}
	}

	//sharedInstance->binded_listener.remove(listener);
	//cout << sharedInstance->binded_listener.size() << endl;
}

void EventManager::Invoke(string name)
{
	map<string, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Invoke();
		}
	}
}

void EventManager::Invoke(string name, bool value)
{
	map<string, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Invoke(value);
		}
	}
}

void EventManager::Invoke(string name, int value)
{
	map<string, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Invoke(value);
		}
	}
}

void EventManager::Invoke(string name, float value)
{
	map<string, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Invoke(value);
		}
	}
}

void EventManager::Invoke(string name, vec2 value)
{
	map<string, list<EventListener*>>::iterator iterator = sharedInstance->binded_events.find(name);
	if (iterator != sharedInstance->binded_events.end())
	{
		for (auto const& listener : iterator->second)
		{
			listener->Invoke(value);
		}
	}
}
