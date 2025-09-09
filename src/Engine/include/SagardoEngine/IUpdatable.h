#ifndef SAGARDOENGINE_IUPDATABLE_H
#define SAGARDOENGINE_IUPDATABLE_H

namespace SagardoEngine
{
    class IUpdatable
    {
        public:
            virtual void Update(float dt) = 0;

        protected:
            virtual ~IUpdatable() = default;
    };
}

#endif //SAGARDOENGINE_IUPDATABLE_H
