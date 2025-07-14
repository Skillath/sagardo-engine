#ifndef MAIN_CPP
#define MAIN_CPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "glad/glad.h" 
#include "GLFW/glfw3.h"
#include <print>

void OnWindowResized(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(void)
{  
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    const auto window = glfwCreateWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Hello World",
        nullptr,
        nullptr);
    
    if (window == nullptr)
    {
        std::println("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::println("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnWindowResized);  

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {        
        /* Render here */
        processInput(window);

        //RENDERING!
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Poll for and process events */
        glfwPollEvents();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }
    
    
    glfwTerminate();
    return 0;
}

void OnWindowResized(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

/*
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
