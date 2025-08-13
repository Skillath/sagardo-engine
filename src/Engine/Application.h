#ifndef APPLICATION_H
#define APPLICATION_H

#include "Scene.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace SagardoEngine
{
    struct ApplicationSettings
    {
        const char* Name;
        const unsigned int Width;
        const unsigned int Height;
    };
    
    class Application
    {
    private:
        const ApplicationSettings _settings;
        Scene* _initialScene;

    public:
        explicit Application(
            const ApplicationSettings& settings,
            Scene* initialScene);

        [[nodiscard]]
        int Run() const;

    private:
        static void OnWindowResized(GLFWwindow* window, int width, int height);
        static void ProcessInput(GLFWwindow *window);
    };
}

#endif //APPLICATION_H
