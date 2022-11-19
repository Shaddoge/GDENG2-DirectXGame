#pragma once
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "Vector3D.h"
#include "GameObject.h"

using namespace reactphysics3d;
class PhysicsComponent : public Component
{
public:
	PhysicsComponent(String name, GameObject* owner);
	~PhysicsComponent();
	void Perform(float deltaTime) override;
	RigidBody* GetRigidBody();

private:
	float mass = 5.0f; //kg
	RigidBody* rigidBody;
};

