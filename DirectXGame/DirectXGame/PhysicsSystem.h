#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>
	
using namespace reactphysics3d;

class PhysicsComponent;
class PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	typedef std::vector<PhysicsComponent*> ComponentList;

	PhysicsSystem();
	~PhysicsSystem();

	void RegisterComponent(PhysicsComponent* component);
	void UnregisterComponent(PhysicsComponent* component);
	void UnregisterComponentByName(String name);
	PhysicsComponent* FindComponentByName(String name);
	ComponentList GetAllComponents();

	void UpdateAllComponents();
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

private:
	ComponentTable componentTable;
	ComponentList componentList;

	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
};

