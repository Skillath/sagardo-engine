#ifndef SAGARDOENGINE_TIMEPROVIDER_H
#define SAGARDOENGINE_TIMEPROVIDER_H

namespace SagardoEngine
{
    class TimeProvider 
    {
    private:
        static double _deltaTime;
        static double _lastFrameTime;
        
    public:
        static double GetTime();
        static double GetDeltaTime();
        static void UpdateDeltaTime();
        static void Reset(); // call once after glfwInit()
    };
}
#endif //SAGARDOENGINE_TIMEPROVIDER_H