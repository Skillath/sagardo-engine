#ifndef APPLICATION_H
#define APPLICATION_H

#include "Scene.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

namespace SagardoEngine
{
    struct ApplicationSettings
    {
        const std::string Name;
        const unsigned int Width;
        const unsigned int Height;
    };
    
    class Application
    {
    private:
        const ApplicationSettings _settings;
        Scene& _initialScene;

    public:
        explicit Application(
            ApplicationSettings  settings,
            Scene& initialScene);

        [[nodiscard]]
        int Run() const;

    private:
        static void OnWindowResized(GLFWwindow* window, int width, int height);
        static void ProcessInput(GLFWwindow *window);
    };
}

#endif //APPLICATION_H
