#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "raylib.h"
#include "Engine/Scene.h"
#include "Engine/Components.h"
#include "Engine/RenderPipeline.h"

using namespace SagardoEngine;

void Setup();
void Destroy();

int main()
{
    Setup();

    Scene gameContextScene("NewScene");
    
    CameraComponent cameraComponent =
    {
        .Fov = 45.f,
        .Target = Vector3{0, 10, 0},
        .Up = Vector3{0, 1, 0},
        .Projection = CAMERA_PERSPECTIVE,
    };

    auto modelGameObject = gameContextScene.NewGameObject("3D Model");
    modelGameObject->AddComponent<FileLoaderComponent>(
    {
        .Path = "/res/models/Fox.glb",
    });
    
    modelGameObject->AddComponent<ModelComponent>({ });
    modelGameObject->AddComponent<ModelAnimationComponent>({ });

    auto cameraObject = gameContextScene.NewGameObject("Camera");
    cameraObject->AddComponent(cameraComponent);
    cameraObject->RemoveComponent<PositionComponent>();
    cameraObject->AddComponent<PositionComponent>(
    {
        .X = 50.f,
        .Y = 50.f,
        .Z = 50.f,
    });

    gameContextScene.Start();

    auto cameraRef = cameraObject->GetComponent<CameraRefComponent>();
    RenderPipeline renderer(&gameContextScene, &cameraRef);

    while (!WindowShouldClose())
    {
        const auto dt = GetFrameTime();
        gameContextScene.Update(dt);
        renderer.Render();
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

#endif
