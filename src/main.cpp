#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "raylib.h"
#include "Engine/Scene.h"
#include "Engine/Components.h"

using namespace SagardoEngine;

void Setup();
void Destroy();
Scene* SetupScene();

int main()
{
    Setup();

    auto gameContextScene = *SetupScene();

    gameContextScene.Start();

    while (!WindowShouldClose())
    {
        const auto dt = GetFrameTime();
        gameContextScene.Update(dt);

        DrawFPS(0,0);
    }

    gameContextScene.Stop();

    Destroy();

    return 0;
}

void Setup()
{
    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Game Engine");
    
    InitAudioDevice();

    SetTargetFPS(144);
}

void Destroy()
{
    CloseAudioDevice();
    CloseWindow();
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
    
        modelGameObject->AddComponent<ModelComponent>({ });
        modelGameObject->AddComponent<ModelAnimationComponent>({ });
        modelGameObject->AddComponent<PositionComponent>({
            .X = i * 2.f,
            .Y = 0,
            .Z = i * 1.f,
        });
        modelGameObject->AddComponent<ScaleComponent>(
        {
            .X = 0.1f,
            .Y = 0.1f,
            .Z = 0.1f,
        });
    }

    auto cameraObject = gameContextScene->NewGameObject("Camera");
    cameraObject->AddComponent<CameraComponent>(
    {
        .Fov = 45.f,
        .Target = Vector3{0, 10, 0},
        .Up = Vector3{0, 1, 0},
        .Projection = CAMERA_PERSPECTIVE,
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
