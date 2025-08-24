#ifndef SAGARDOENGINE_ISTOPABLE_H
#define SAGARDOENGINE_ISTOPABLE_H

namespace SagardoEngine
{
    class IStopable
    {
    public:
        virtual void Stop() = 0;

    protected:
        virtual ~IStopable() = default;
    };
}

#endif //SAGARDOENGINE_ISTOPABLE_H
