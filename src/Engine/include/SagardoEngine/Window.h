#ifndef SAGARDOENGINE_WINDOW_H
#define SAGARDOENGINE_WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

namespace SagardoEngine
{
    struct WindowOptions
    {        
        bool IsFullscreen = false;
        bool IsResizable = true;
    };
    
    class Window final
    {
    private:
        unsigned int _width;
        unsigned int _height;
        std::string _title;

        const WindowOptions _options;

        GLFWwindow* _glfwWindow = nullptr;
    public:
        Window(
            unsigned int width,
            unsigned int height,
            std::string_view title,
            WindowOptions windowOptions = WindowOptions());

        void SetWindowTitle(const std::string_view& title);
        
        ~Window();

    private:
        void OnWindowResized(GLFWwindow* window, int width, int height);
    };
} // SagardoEngine

#endif //SAGARDOENGINE_WINDOW_H