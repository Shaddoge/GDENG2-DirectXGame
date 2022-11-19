#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner) : Component(name, Component::ComponentType::Physics, owner)
{
	BaseComponentSystem::GetInstance()->GetPhysicsSystem()->RegisterComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsWorld();

	// Create Rigidbody
	Vector3D local_scale = this->GetOwner()->GetLocalScale();
	Vector3D local_pos = this->GetOwner()->GetLocalPosition();
	Vector3D local_rot = this->GetOwner()->GetLocalRotation();
	Transform transform(Vector3(local_pos.x, local_pos.y, local_pos.z), Quaternion::fromEulerAngles(local_rot.x, local_rot.y, local_rot.z));
	
	//transform.setFromOpenGL((decimal*)this->GetOwner()->GetPhysicsLocalMatrix());


	transform.setPosition(Vector3(local_pos.x, local_pos.y, local_pos.z));
	transform.setOrientation(Quaternion::fromEulerAngles(Vector3(local_rot.x, local_rot.y, local_rot.z)));
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(local_scale.x / 1, local_scale.y / 1, local_scale.z / 1));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();

	//float matrix[16];
	//transform.getOpenGLMatrix(matrix);
	this->GetOwner()->SetRotation(Vector3D(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z));
	this->GetOwner()->SetPosition(Vector3D(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));

	//this->GetOwner()->RecomputeMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UnregisterComponent(this);
	Component::~Component();
}

void PhysicsComponent::Perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	//float matrix[16];
	//transform.getOpenGLMatrix(matrix);

	//this->GetOwner()->RecomputeMatrix(matrix);

	this->GetOwner()->SetRotation(Vector3D(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z));
	this->GetOwner()->SetPosition(Vector3D(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));
	
	Vector3D local_pos = this->GetOwner()->GetLocalPosition();
	//std::cout << transform.getPosition().y << " = " << local_pos.y << std::endl;
	//std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* PhysicsComponent::GetRigidBody()
{
	return rigidBody;
}
