#include "../include/SagardoEngine/TimeProvider.h"
#include <GLFW/glfw3.h>

namespace SagardoEngine
{
    double TimeProvider::_deltaTime = 0.0;
    double TimeProvider::_lastFrameTime = 0.0;

    double TimeProvider::GetTime()
    {
        return glfwGetTime(); // requires glfwInit() done earlier
    }

    double TimeProvider::GetDeltaTime()
    {
        return _deltaTime;
    }

    void TimeProvider::UpdateDeltaTime()
    {
        const double current = GetTime();
        _deltaTime = current - _lastFrameTime;
        _lastFrameTime = current;
    }

    void TimeProvider::Reset()
    {
        _lastFrameTime = GetTime();
        _deltaTime = 0.0;
    }
}

