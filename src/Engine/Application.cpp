#include "Application.h"

#include <print>
#include <format>
#include <utility>

#include "TimeProvider.h"
#include <Debug/OpenGlDebug.h>

namespace SagardoEngine
{
    Application::Application(
        ApplicationSettings settings,
        Scene& initialScene) :
            _settings(std::move(settings)),
            _initialScene(initialScene)
    {
    }

    int Application::Run() const
    {
        if (!glfwInit())
        {
            std::println("Failed to initialize GLFW!");
            std::exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  
        
        /* Create a windowed mode window and its OpenGL context */
        const auto window = glfwCreateWindow(
            _settings.Width,
            _settings.Height,
            _settings.Name.c_str(),
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

        if (!gladLoadGL(glfwGetProcAddress))
        {
            std::println("Failed to initializ GLAD");
            std::exit(EXIT_FAILURE);
        }

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
            glDebugMessageCallback(Debug::GlDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);            
        }

        // Optional: at startup print device info
        std::fprintf(stderr, "GL %s | %s | %s\n",
            reinterpret_cast<const char*>(glGetString(GL_VERSION)),
            reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
            reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

        glEnable(GL_DEPTH_TEST);

        TimeProvider::Reset();

        double lastTime = TimeProvider::GetTime();
        int nbFrames = 0;
        
        _initialScene.Start();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            const double currentTime = TimeProvider::GetTime();
            nbFrames++;
            if (currentTime - lastTime >= 1.0)
            { // every second
                const double fps = double(nbFrames) / (currentTime - lastTime);
                std::string message = _settings.Name + "- FPS: " + std::to_string((int)fps);
                glfwSetWindowTitle(window, message.c_str());
                
                nbFrames = 0;
                lastTime = currentTime;
            }

            TimeProvider::UpdateDeltaTime();
            const auto deltaTime = (float)TimeProvider::GetDeltaTime();
            
            ProcessInput(window);
            
            glClearColor(0.f, 0.f, 0.f, 1.0f);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            _initialScene.Update(deltaTime);
        
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        _initialScene.Stop();
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
}
