#pragma once
#include <iostream>

class PhysicsSystem;	
class BaseComponentSystem
{
public:
	typedef std::string String;

	static BaseComponentSystem* GetInstance();
	static void Initialize();
	static void Destroy();

	PhysicsSystem* GetPhysicsSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator=(BaseComponentSystem const&) {};
	static BaseComponentSystem* sharedInstance;

	PhysicsSystem* physicsSystem;
};

