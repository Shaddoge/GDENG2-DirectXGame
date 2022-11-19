#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::GetInstance()
{
    return sharedInstance;
}

void SceneCameraHandler::Initialize()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::Destroy()
{
    delete sharedInstance;
}

void SceneCameraHandler::Update()
{
    this->scene_camera->Update(EngineTime::GetDeltaTime());
}

Camera* SceneCameraHandler::GetCamera()
{
    return this->scene_camera;
}

Matrix4x4 SceneCameraHandler::GetSceneCameraViewMatrix()
{
    return this->scene_camera->GetViewMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
    this->scene_camera = new Camera("SceneCamera");
}
SceneCameraHandler::~SceneCameraHandler()
{
    delete this->scene_camera;
}