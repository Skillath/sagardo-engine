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
    
    int result = 0;
    try
    {
        result = app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<std::endl;
        return -1;
    }

    return result;
}

Scene* SetupScene()
{
    const auto gameContextScene = new Scene("NewScene");

    for (auto i = 0; i < 5; i++)
    {        
        auto modelGameObject = gameContextScene->NewGameObject(("3D Model{" + std::to_string(i) + "}").c_str());
        modelGameObject->AddComponent<TriangleComponent>(SetupTriangle());
        
        modelGameObject->AddComponent<PositionComponent>(
        {
            .X = i * 2.f,
            .Y = i * 2.f,
            .Z = i * 2.f,
        });
    }

    return gameContextScene;
}

TriangleComponent SetupTriangle()
{
    return TriangleComponent
    {
        .Vertices = new float[20]
        {
            // positions          // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
           -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        },
        .Indices = new unsigned int[6]
        {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        },
        .TextCoords = new float[6]
        {
            0.0f, 0.0f,  // lower-left corner  
            1.0f, 0.0f,  // lower-right corner
            0.5f, 1.0f   // top-center corner
        },
        .VerticesSize = sizeof(float[20]),
        .IndicesSize = sizeof(unsigned int[6]),
        .TextCoordsSize = sizeof(float[6]),
        .WrappingOptions = GL_REPEAT,
        .FragmentShaderPath = "src/res/shaders/color.frag",
        .VertexShaderPath = "src/res/shaders/color.vert",
        .TexturePath = "src/res/textures/wall.jpg",
        .AwesomeFaceTexturePath = "src/res/textures/awesomeface.png",
    };
}
#endif
