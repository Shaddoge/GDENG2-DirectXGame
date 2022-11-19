#pragma once
#include "Camera.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* GetInstance();
	static void Initialize();
	static void Destroy();

	void Update(); //TODO: Game object manager should perform update of all game objects

	Camera* GetCamera();

	Matrix4x4 GetSceneCameraViewMatrix();
private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};             // copy constructor is private
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};  // assignment operator is private*/
	static SceneCameraHandler* sharedInstance;

	Camera* scene_camera;
};

