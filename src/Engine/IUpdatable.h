#ifndef IUPDATABLE_H
#define IUPDATABLE_H

namespace Engine
{
    class IUpdatable
    {
        public:
            virtual void Update(float dt) = 0;

        protected:
            virtual ~IUpdatable() = default;
    };

    class IStartable
    {
        public:
            virtual void Start() = 0;

        protected:
            virtual ~IStartable() = default;
    };

    class IStopable
    {
        public:
            virtual void Stop() = 0;

        protected:
            virtual ~IStopable() = default;
    };
}

#endif //IUPDATABLE_H
