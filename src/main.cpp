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
    const auto gameContextScene = new Scene("NewScene");

    auto go = gameContextScene->NewGameObject("Triangle");
    go->AddComponent<TriangleComponent>(SetupTriangle());

    for (auto i = 0; i < 1; i++)
    {
        auto modelGameObject = gameContextScene->NewGameObject("3D Model");
        modelGameObject->AddComponent<FileLoaderComponent>(
        {
            .Path = "/res/models/Fox.glb",
        });
        
        modelGameObject->AddComponent<PositionComponent>({
            .X = i * 2.f,
            .Y = 0,
            .Z = i * 1.f,
        });
    }

    return gameContextScene;
}

TriangleComponent SetupTriangle()
{
    return TriangleComponent
    {
        .Vertices = new float[18]
        {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
        },

        .VerticesSize = sizeof(float[18]),
        .Indices = new unsigned int[6]
        {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        },
        .IndicesSize = sizeof(unsigned int[6]),
        .FragmentShaderPath = "res/shaders/color.frag",
        .VertexShaderPath = "res/shaders/color.vert",
    };
}
#endif
