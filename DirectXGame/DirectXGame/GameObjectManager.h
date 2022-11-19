#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "GameObject.h"

class EditorAction;
class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<GameObject*> List;
	typedef std::unordered_map<String, GameObject*> HashTable;

	static GameObjectManager* GetInstance();
	static void Initialize();
	static void Destroy();

	GameObject* FindObjectByName(String name);
	List GetAllObjects();
	int ActiveObjects();
	void UpdateAll();
	void RenderAll(int viewportWidth, int viewportHeight);
	void AddObject(GameObject* gameObject);
	void CreateObject(GameObject::PrimitiveType type);
	void CreateObjectFromFile(String name, GameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale);
	void DeleteObject(GameObject* gameObject);
	void DeleteObjectByName(String name);
	void SetSelectedObject(String name);
	void SetSelectedObject(GameObject* gameObject);
	GameObject* GetSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	HashTable gameObjectMap;
	List gameObjectList;

	GameObject* selectedObject = NULL;
};