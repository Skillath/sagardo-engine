#ifndef TIMEPROVIDER_H
#define TIMEPROVIDER_H

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
#endif //TIMEPROVIDER_H