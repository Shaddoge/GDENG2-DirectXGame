#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Cube.h"
#include "Plane.h"
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "Vector3D.h"
#include "SceneCameraHandler.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::GetInstance()
{
	return sharedInstance;
}

void GameObjectManager::Initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::Destroy()
{
	sharedInstance->gameObjectMap.clear();
	sharedInstance->gameObjectList.clear();
	delete sharedInstance;
}

GameObject* GameObjectManager::FindObjectByName(String name)
{
	if (this->gameObjectMap[name] != NULL)
	{
		return this->gameObjectMap[name];
	}
	else
	{
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

GameObjectManager::List GameObjectManager::GetAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::ActiveObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::UpdateAll()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) 
	{	
		if (this->gameObjectList[i]->IsEnabled())
		{
			this->gameObjectList[i]->SetViewMatrix(SceneCameraHandler::GetInstance()->GetCamera()->GetInverseWorldCam());
			this->gameObjectList[i]->Update(EngineTime::GetDeltaTime());
		}
	}
}

void GameObjectManager::RenderAll(int viewportWidth, int viewportHeight)
{
	for (int i = 0; i < this->gameObjectList.size(); i++)
	{
		if (this->gameObjectList[i]->IsEnabled())
		{
			this->gameObjectList[i]->Draw(viewportWidth, viewportHeight);
		}
	}
}

void GameObjectManager::AddObject(GameObject* gameObject)
{
	if (this->gameObjectMap[gameObject->GetName()] != NULL) {
		int count = 1;
		String revisedString = gameObject->GetName() + " " + "(" + std::to_string(count) + ")";
		while (this->gameObjectMap[revisedString] != NULL) {
			count++;
			revisedString = gameObject->GetName() + " " + "(" + std::to_string(count) + ")";
		}
		gameObject->name = revisedString;
		this->gameObjectMap[revisedString] = gameObject;
	}
	else {
		this->gameObjectMap[gameObject->GetName()] = gameObject;
	}

	this->gameObjectList.push_back(gameObject);
	gameObject->Awake();
}

void GameObjectManager::CreateObject(GameObject::PrimitiveType type)
{
	if (type == GameObject::PrimitiveType::CUBE) {
		Cube* cube = new Cube("Cube");
		cube->SetPosition(0.0f, 0.0f, 0.0f);
		cube->SetScale(1.0f, 1.0f, 1.0f);
		this->AddObject(cube);
	}

	else if (type == GameObject::PrimitiveType::PLANE) {
		Plane* plane = new Plane("Plane");
		this->AddObject(plane);
	}

	/*else if (type == GameObject::PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube("Cube_Textured");
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->AddObject(cube);
	}*/

	else if (type == GameObject::PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube("Cube_Physics");
		this->AddObject(cube);
	}

	else if (type == GameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane("Plane_Physics");
		this->AddObject(plane);
	}
}

void GameObjectManager::CreateObjectFromFile(String name, GameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale)
{
	if (type == GameObject::PrimitiveType::CUBE) {
		Cube* cube = new Cube(name);
		cube->SetPosition(position);
		cube->SetRotation(rotation);
		cube->SetScale(scale);
		this->AddObject(cube);
	}

	else if (type == GameObject::PrimitiveType::PLANE) {
		Plane* plane = new Plane(name);
		plane->SetPosition(position);
		plane->SetRotation(rotation);
		plane->SetScale(scale);
		this->AddObject(plane);
	}

	/*else if (type == GameObject::PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube(name);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->AddObject(cube);
	}*/

	else if (type == GameObject::PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube(name);
		cube->SetPosition(position);
		cube->SetRotation(rotation);
		cube->SetScale(scale);
		this->AddObject(cube);
	}

	else if (type == GameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(name);
		plane->SetPosition(position);
		plane->SetRotation(rotation);
		plane->SetScale(scale);
		this->AddObject(plane);
	}
}

void GameObjectManager::DeleteObject(GameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->GetName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}

	delete gameObject;
}

void GameObjectManager::DeleteObjectByName(String name)
{
	GameObject* object = this->FindObjectByName(name);

	if (object != NULL) {
		this->DeleteObject(object);
	}
}

void GameObjectManager::SetSelectedObject(String name)
{
	if (this->gameObjectMap[name] != NULL) {
		this->SetSelectedObject(this->gameObjectMap[name]);
	}
}

void GameObjectManager::SetSelectedObject(GameObject* gameObject)
{
	this->selectedObject = gameObject;
}

GameObject* GameObjectManager::GetSelectedObject()
{
	return this->selectedObject;
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}