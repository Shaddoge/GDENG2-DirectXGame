#include "PhysicsCube.h"

PhysicsCube::PhysicsCube(String name, bool skipInit) : Cube(name, skipInit)
{
	//std::cout << "Physics Cube Construct" << std::endl;
	this->objectType = GameObject::PrimitiveType::PHYSICS_CUBE;
	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->SetScale(0.5f, 0.5f, 0.5f);
	this->UpdateLocalMatrix();
}

void PhysicsCube::Awake()
{
	//std::cout << "Physics Cube Awake" << std::endl;
	GameObject::Awake();
	this->componentAttached = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	//std::cout << componentAttached->GetName() << std::endl;
	this->AttachComponent(this->componentAttached);
	this->SetPosition(0.0f, 4.0f, 0.0f);
}

PhysicsCube::~PhysicsCube()
{
	this->DetachComponent(this->componentAttached);
	delete this->componentAttached;
	Cube::~Cube();
}

void PhysicsCube::Update(float deltaTime)
{
	//std::cout << this->componentAttached->GetName() << std::endl;
	Cube::Update(deltaTime);
	
	//std::cout << "My object is updating: " << this->name << "\n";
}

void PhysicsCube::Draw(int width, int height)
{
	Cube::Draw(width, height);
}