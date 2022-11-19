#include "Component.h"

Component::Component(String name, Component::ComponentType type, GameObject* owner)
{
	this->name = name;
	this->owner = owner;
	this->type = type;
}

Component::~Component()
{
	this->owner = NULL;
	this->type = NotSet;
}

void Component::AttachOwner(GameObject* owner)
{
	this->owner = owner;
}

void Component::DetachOwner()
{
	this->owner = NULL;
}

GameObject* Component::GetOwner()
{
	return this->owner;
}

Component::ComponentType Component::GetType()
{
	return type;
}

String Component::GetName()
{
	return name;
}
