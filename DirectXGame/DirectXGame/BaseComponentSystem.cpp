#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = NULL;

BaseComponentSystem* BaseComponentSystem::GetInstance()
{
	return sharedInstance;
}

void BaseComponentSystem::Initialize()
{
	sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::Destroy()
{
	delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::GetPhysicsSystem()
{
	return this->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	this->physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
	delete this->physicsSystem;
}
