#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include <iostream>
#include "EngineTime.h"

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

PhysicsSystem::~PhysicsSystem()
{
	delete this->physicsCommon;
}

void PhysicsSystem::RegisterComponent(PhysicsComponent* component)
{
	std::cout << "Registering Physics component: " << component->GetName() << "\n";
	this->componentTable[component->GetName()] = component;
	this->componentList.push_back(component);
}

void PhysicsSystem::UnregisterComponent(PhysicsComponent* component)
{
	std::cout << "Unregistering Physics component: " << component->GetName() << "\n";

	if (this->componentTable[component->GetName()] != NULL) {
		this->componentTable.erase(component->GetName());
		int index = -1;
		for (int i = 0; i < this->componentList.size(); i++) {
			if (this->componentList[i] == component) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			this->componentList.erase(this->componentList.begin() + index);
		}
	}
	else {
		std::cout << "Component " << component->GetName() << " not registered in physics component. \n";
	}
}

void PhysicsSystem::UnregisterComponentByName(String name)
{
	if (this->componentTable[name] != NULL) {
		this->UnregisterComponent(this->componentTable[name]);
	}
}

PhysicsComponent* PhysicsSystem::FindComponentByName(String name)
{
	if (this->componentTable[name] == NULL) {
		std::cout << "Component " << name << " not registered in physics component. \n";
	}

	return this->componentTable[name];
}

std::vector<PhysicsComponent*> PhysicsSystem::GetAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::UpdateAllComponents()
{
	if (EngineTime::GetDeltaTime() > 0.0f) {
		//update physics world
		this->physicsWorld->update(EngineTime::GetDeltaTime());
		for (int i = 0; i < this->componentList.size(); i++) {
			this->componentList[i]->Perform(EngineTime::GetDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::GetPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::GetPhysicsCommon()
{
	return this->physicsCommon;
}
