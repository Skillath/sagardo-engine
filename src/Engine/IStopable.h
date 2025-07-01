#ifndef ISTOPABLE_H
#define ISTOPABLE_H

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

#endif //ISTOPABLE_H
