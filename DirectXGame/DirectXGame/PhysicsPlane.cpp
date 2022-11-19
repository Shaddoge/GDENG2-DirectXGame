#include "PhysicsPlane.h"

PhysicsPlane::PhysicsPlane(String name) : Plane(name)
{
	std::cout << "Physics Plane Construct" << std::endl;
	this->objectType = GameObject::PrimitiveType::PHYSICS_PLANE;
	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->SetScale(50.0f, 0.1f, 50.0f);
	this->UpdateLocalMatrix();
}

PhysicsPlane::~PhysicsPlane()
{
	this->DetachComponent(this->componentAttached);
	delete this->componentAttached;
	Plane::~Plane();
}

void PhysicsPlane::Awake()
{
	std::cout << "Physics Plane Awake" << std::endl;
	GameObject::Awake();
	this->componentAttached = new PhysicsComponent("PhysicsComponent_" + this->name, this);

	this->FindComponentOfType(Component::ComponentType::Physics, "PhysicsComponent");
	this->componentAttached->GetRigidBody()->setType(BodyType::KINEMATIC);

	this->AttachComponent(this->componentAttached);
}

void PhysicsPlane::Update(float deltaTime)
{
	Plane::Update(deltaTime);

	//std::cout << "My object is updating: " << this->name << "\n";
}

void PhysicsPlane::Draw(int width, int height)
{
	Plane::Draw(width, height);
}