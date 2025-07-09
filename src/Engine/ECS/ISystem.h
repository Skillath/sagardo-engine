//
// Created by xabi on 6/07/25.
//

#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "flecs.h"

namespace SagardoEngine::Ecs
{
    class ISystem
    {
    protected:
        ~ISystem() = default;

    public:
        virtual void Run(flecs::world& world, const float deltaTime) = 0;
    };
}

#endif //ISYSTEM_H
