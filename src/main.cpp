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
TriangleComponent SetupTriangle();

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

    camera->AddComponent<CameraComponent>(
    {
        
    });

    const auto light = gameContextScene->NewGameObject("Light");
    light->AddComponent<PositionComponent>(
    {
        .X = 50.f,
        .Y = 50.f,
        .Z = 50.f,
    });
    light->AddComponent<LightComponent>(
    {
        .Color = Colors32::White,
        .LightIntensity = 1.f,
    });

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
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };
    
    return TriangleComponent
    {
        .Vertices = new float[]
        {
            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f,  
             0.5f,  0.5f, -0.5f,  
             0.5f,  0.5f, -0.5f,  
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f, -0.5f,  0.5f, 
             0.5f, -0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 

            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 

             0.5f,  0.5f,  0.5f,  
             0.5f,  0.5f, -0.5f,  
             0.5f, -0.5f, -0.5f,  
             0.5f, -0.5f, -0.5f,  
             0.5f, -0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  

            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f,  
             0.5f, -0.5f,  0.5f,  
             0.5f, -0.5f,  0.5f,  
            -0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f,  0.5f, -0.5f, 
             0.5f,  0.5f, -0.5f,  
             0.5f,  0.5f,  0.5f,  
             0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f, 
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
        .VerticesSize = sizeof(vertices),
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
