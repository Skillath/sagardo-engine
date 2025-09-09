#include "SagardoEngine/Window.h"

#include <print>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace SagardoEngine
{
    Window::Window(
        const unsigned int width,
        const unsigned int height,
        const std::string_view title,
        const WindowOptions windowOptions) :
        _width(width),
        _height(height),
        _title(title),
        _options(windowOptions)
    {
        _glfwWindow = glfwCreateWindow(
            static_cast<int>(width),
            static_cast<int>(height),
            title.data(),
            nullptr,
            nullptr);

        if (_glfwWindow == nullptr)
        {
            std::println("Failed to create GLFW window");
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(_glfwWindow);
        
        //glfwSetFramebufferSizeCallback(_glfwWindow, Window::OnWindowResized);
    }

    void Window::SetWindowTitle(const std::string_view& title)
    {
        _title = title;
        glfwSetWindowTitle(_glfwWindow, title.data());
    }

    Window::~Window()
    {
        glfwDestroyWindow(_glfwWindow);
        _glfwWindow = nullptr;
    }

    void Window::OnWindowResized(GLFWwindow* window, const int width, const int height)
    {
        _width = width;
        _height = height;
        glViewport(0, 0, width, height);
    }
} // SagardoEngine