#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "raylib.h"
#include "Engine/Scene.h"
#include "Engine/Components.h"
#include "Engine/RenderPipeline.h"

void Setup();

void Destroy();

int main()
{
    Setup();
    
    SagardoEngine::RenderPipeline renderer;

    SagardoEngine::Scene gameContextScene("NewScene");

    SagardoEngine::CameraComponent cameraComponent =
    {
        45.f,
        Vector3{0, 10, 0},
        Vector3{0, 1, 0},
        CAMERA_PERSPECTIVE,
    };

    auto modelGameObject = gameContextScene.NewGameObject("3D Model");
    modelGameObject->AddComponent<SagardoEngine::FileLoaderComponent>(
    {
        "/res/models/Fox.glb",
    });
    
    modelGameObject->AddComponent<SagardoEngine::ModelComponent>({  });
    modelGameObject->AddComponent<SagardoEngine::ModelAnimationComponent>({});

    auto cameraObject = gameContextScene.NewGameObject("Camera");
    cameraObject->AddComponent(cameraComponent);
    cameraObject->RemoveComponent<SagardoEngine::PositionComponent>();
    cameraObject->AddComponent<SagardoEngine::PositionComponent>(
    {
        50.f,
        50.f,
        50.f,
    });

    gameContextScene.Start();

    while (!WindowShouldClose())
    {
        const auto dt = GetFrameTime();
        
        renderer.Render();

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            const auto cameraRef = cameraObject->GetComponent<SagardoEngine::CameraRefComponent>();
            const auto camera = cameraRef.CameraRef;

            BeginMode3D(camera);
            {
                gameContextScene.Update(dt);
            }
            EndMode3D();

            DrawFPS(0,0);
        }
        EndDrawing();
    }

    gameContextScene.Stop();

    Destroy()

    return 0;
}

void Setup()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Engine");
    InitAudioDevice();

    SetTargetFPS(144);
}

void Destroy()
{
    CloseAudioDevice();
    CloseWindow();
}

#endif
