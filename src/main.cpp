#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "raylib.h"
#include "Engine/Scene.hpp"
#include "Engine/Components.hpp"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Engine");
    InitAudioDevice();

    SetTargetFPS(144);

    Engine::Scene gameContextScene("NewScene");

    Engine::CameraComponent cameraComponent =
    {
        45.f,
        Vector3{0, 0, 10},
        Vector3{0, 1, 0},
        CAMERA_PERSPECTIVE,
    };

    Engine::ModelLoaderComponent modelLoaderComponent =
    {
        "res/models/Steve.obj",
    };

    auto modelGameObject = gameContextScene.NewGameObject("3D Model");
    modelGameObject->AddComponent(modelLoaderComponent);

    auto cameraObject = gameContextScene.NewGameObject("Camera");
    cameraObject->AddComponent(cameraComponent);

    gameContextScene.Start();

    while (!WindowShouldClose())
    {
        const auto dt = GetFrameTime();

        BeginDrawing();
        {
            ClearBackground(BLACK);

            const auto cameraRef = cameraObject->GetComponent<Engine::CameraRefComponent>();
            const auto camera = cameraRef.CameraRef;

            BeginMode3D(camera);
            {
                gameContextScene.Update(dt);
                gameContextScene.Render3D();
            }
            EndMode3D();
        }
        EndDrawing();
    }

    gameContextScene.Stop();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

#endif
