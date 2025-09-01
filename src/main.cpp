#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include <iostream>
#include <string>

#include "Application.h"
#include "ComponentUtils.h"
#include "Scene.h"

using namespace SagardoEngine;

Scene* SetupScene();

int main(void)
{
    const ApplicationSettings settings
    {
        .Name = "Hello World",
        .Width = SCREEN_WIDTH,
        .Height = SCREEN_HEIGHT,
    };

    const auto scene = SetupScene();
    const Application app(settings, *scene);
    
    int result = 0;
    try
    {
        result = app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<std::endl;
        delete scene;
        return -1;
    }

    delete scene;
    return result;
}

Scene* SetupScene()
{
    const auto gameContextScene = new Scene("NewScene");
    const auto camera = gameContextScene->NewGameObject("Camera");
    camera->AddComponent<PositionComponent>(
    {
        .X = 0,
        .Y = 0,
        .Z = 3.f,
    });

    camera->AddComponent<CameraComponent>({});

    const auto light = gameContextScene->NewGameObject("Light");
    light->AddComponent<PositionComponent>(
    {
        .X = 50.f,
        .Y = 50.f,
        .Z = 50.f,
    });
    light->AddComponent<LightComponent>(
    {
        .Red = 1.f,
        .Green = 1.f,
        .Blue = 1.f,
        .LightIntensity = 1.f,
    });

    for (auto i = 0; i < 1; i++)
    {        
        const auto& modelGameObject = gameContextScene->NewGameObject(("3D Model{" + std::to_string(i) + "}").c_str());
        modelGameObject->AddComponent<FileLoaderComponent>(
        {
                .Path = "res/models/backpack/backpack.obj",
        });

        modelGameObject->AddComponent<ModelComponent>({});
        
        modelGameObject->AddComponent<PositionComponent>(
        {
            .X = 2,
            .Y = 0.f,
            .Z = i * 2.f,
        });

        modelGameObject->AddComponent<ScaleComponent>(
        {
            .X = 0.5f,
            .Y = 0.5f,
            .Z = 0.5f,
        });

        modelGameObject->AddComponent<RotatorComponent>(
        {
            .RotationSpeed = glm::vec3{0.f, 10.f, 0.f},
        });
    }

    return gameContextScene;
}
#endif
