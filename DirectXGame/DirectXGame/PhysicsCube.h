#pragma once
#include "Cube.h"
#include "PhysicsComponent.h"

class PhysicsCube : public Cube
{
public:
	PhysicsCube(String name, bool skipInit = false);
	~PhysicsCube();

	void Update(float deltaTime) override;
	void Draw(int width, int height) override;
protected:
	float mass = 3.0f;
	PhysicsComponent* componentAttached;

	void Awake() override;
};

