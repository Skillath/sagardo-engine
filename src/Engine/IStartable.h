#ifndef ISTARTABLE_H
#define ISTARTABLE_H

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

#endif //ISTARTABLE_H
