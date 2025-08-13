#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include <iostream>

#include "Application.h"
#include "ComponentUtils.h"
#include "Scene.h"

using namespace SagardoEngine;

Scene* SetupScene();
TriangleComponent SetupTriangle();

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
        std::cerr << e.what() <<std::endl;
        return -1;
    }

    return 0;
}

Scene* SetupScene()
{
    auto gameContextScene = new Scene("NewScene");

    auto go = gameContextScene->NewGameObject("Triangle");
    go->AddComponent<TriangleComponent>(SetupTriangle());
    
    return gameContextScene;

    for (auto i = 0; i < 1; i++)
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

TriangleComponent SetupTriangle()
{
    return TriangleComponent
    {
        .VertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0",
    
        .FragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0",
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        .Vertices = new float [12]
        {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
           -0.5f, -0.5f, 0.0f,  // bottom left
           -0.5f,  0.5f, 0.0f   // top left 
        },

        .NumVertices = sizeof(float[12]),
        .Indices = new unsigned int[6]
        {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        },
        .NumIndices = sizeof(unsigned int[6]),
    };
}
#endif
