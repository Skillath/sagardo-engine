#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "raylib.h"
#include "Engine/Scene.h"
#include "Engine/Components.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Engine");
    InitAudioDevice();

    SetTargetFPS(144);

    SagardoEngine::Scene gameContextScene("NewScene");

    SagardoEngine::CameraComponent cameraComponent =
    {
        45.f,
        Vector3{0, 10, 0},
        Vector3{0, 1, 0},
        CAMERA_PERSPECTIVE,
    };

    auto modelGameObject = gameContextScene.NewGameObject("3D Model");
    modelGameObject->AddComponent<SagardoEngine::ModelLoaderComponent>(
    {
        "/res/models/Fox.glb",
    });

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

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            const auto cameraRef = cameraObject->GetComponent<SagardoEngine::CameraRefComponent>();
            const auto camera = cameraRef.CameraRef;

            BeginMode3D(camera);
            {
                gameContextScene.Update(dt);
                gameContextScene.Render3D();
            }
            EndMode3D();

            DrawFPS(0,0);
        }
        EndDrawing();
    }

    gameContextScene.Stop();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

#endif
