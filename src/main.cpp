#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "glad/gl.h"
#include "GLFW/glfw3.h"

int main(void)
{  
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    auto window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -1;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
/*
void Raylib()
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
}

void Setup()
{
    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Game Engine");
    
    InitAudioDevice();

    SetTargetFPS(144);

    rlDisableBackfaceCulling();
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
*/
#endif
