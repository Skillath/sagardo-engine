#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include <print>

#include "Application.h"
#include "ComponentUtils.h"
#include "Scene.h"

using namespace SagardoEngine;
Scene* SetupScene();

int main(void)
{
    constexpr ApplicationSettings settings
    {
        .Name = "Hello World",
        .Width = SCREEN_WIDTH,
        .Height = SCREEN_HEIGHT,
    };
    
    const Application app(settings, SetupScene());
    
    try
    {
        return app.Run();
    }
    catch(const std::exception& e)
    {
        std::println(e.what());
        return -1;
    }

    return 0;
}

Scene* SetupScene()
{
    auto gameContextScene = new Scene("NewScene");

    for (auto i = 0; i < 100; i++)
    {
        auto modelGameObject = gameContextScene->NewGameObject("3D Model");
        modelGameObject->AddComponent<FileLoaderComponent>(
        {
            .Path = "/res/models/Fox.glb",
        });
    
        //modelGameObject->AddComponent<ModelComponent>({ });
        modelGameObject->AddComponent<ModelAnimationComponent>({ });
        modelGameObject->AddComponent<PositionComponent>({
            .X = i * 2.f,
            .Y = 0,
            .Z = i * 1.f,
        });
    }

    auto cameraObject = gameContextScene->NewGameObject("Camera");
    cameraObject->AddComponent<CameraComponent>(
    {
        .Fov = 45.f,
        .Target = glm::vec3{0, 10, 0},
        .Up = glm::vec3{0, 1, 0},
        //.Projection = CAMERA_PERSPECTIVE,
    });
    
    cameraObject->AddComponent<PositionComponent>(
    {
        .X = 50.f,
        .Y = 50.f,
        .Z = 50.f,
    });

    return gameContextScene;
} 
#endif
