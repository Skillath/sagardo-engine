#ifndef SAGARDOENGINE_ISTARTABLE_H
#define SAGARDOENGINE_ISTARTABLE_H

namespace SagardoEngine
{
    class IStartable
    {
        public:
            virtual void Start() = 0;

        protected:
            virtual ~IStartable() = default;
    };
}

#endif //SAGARDOENGINE_ISTARTABLE_H
