#ifndef TIMEPROVIDER_H
#define TIMEPROVIDER_H

#include "GLFW/glfw3.h"

namespace SagardoEngine
{
    class TimeProvider 
    {
    private:
        static double _deltaTime;
        static double _lastFrameTime;
        
    public:
        static double GetTime()
        {
            return glfwGetTime();
        }

        static double GetDeltaTime()
        {
            return _deltaTime;
        }

        static void UpdateDeltaTime()
        {
            const auto currentFrame = GetTime();
            _deltaTime = currentFrame - _lastFrameTime;
            _lastFrameTime = currentFrame;
        }
    };
}
#endif //TIMEPROVIDER_H