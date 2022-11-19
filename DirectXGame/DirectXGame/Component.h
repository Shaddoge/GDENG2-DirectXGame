#pragma once
#include <iostream>

typedef std::string String;

class GameObject;
class Component
{
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };
	Component(String name, Component::ComponentType type, GameObject* owner);
	~Component();

	void AttachOwner(GameObject* owner);
	void DetachOwner();
	GameObject* GetOwner();
	ComponentType GetType();
	String GetName();

	virtual void Perform(float deltaTime) = 0;
protected:
	GameObject* owner;
	ComponentType type;
	String name;
};

