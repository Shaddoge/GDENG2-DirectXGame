#pragma once
#include "Plane.h"
#include "PhysicsComponent.h"

class PhysicsPlane : public Plane
{
public:
	PhysicsPlane(String name);
	~PhysicsPlane();

	void Update(float deltaTime) override;
	void Draw(int width, int height) override;
private:
	PhysicsComponent* componentAttached;
	void Awake() override;
};