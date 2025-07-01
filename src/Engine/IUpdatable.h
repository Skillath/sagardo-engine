#ifndef IUPDATABLE_H
#define IUPDATABLE_H

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

#endif //IUPDATABLE_H
