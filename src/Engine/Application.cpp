#include "Application.h"

#include <print>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace SagardoEngine;

Application::Application(
    const ApplicationSettings& settings,
    Scene* initialScene) :
        _settings(settings),
        _initialScene(initialScene)
{
}

int Application::Run() const
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::println("Failed to initialize GLFW!");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    const auto window = glfwCreateWindow(
        _settings.Width,
        _settings.Height,
        _settings.Name,
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
    glfwSetFramebufferSizeCallback(window, OnWindowResized);

    /* glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::println("Failed to initialize GLAD");
        return -1;
    }
    
    _initialScene->Start();
    
    double deltaTime = 0;
    double lastFrame = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        std::println("deltaTime: {0}", deltaTime);
        
        /* Render here */
        ProcessInput(window);

        //RENDERING!
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _initialScene->Update(deltaTime);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    _initialScene->Stop();
    glfwTerminate();
    return 0;
}

void Application::OnWindowResized(
    GLFWwindow* window,
    const int width,
    const int height)
{
    glViewport(0, 0, width, height);
}  

void Application::ProcessInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
