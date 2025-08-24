//
// Created by xabi on 6/07/25.
//

#ifndef SAGARDOENGINE_ECS_ISYSTEM_H
#define SAGARDOENGINE_ECS_ISYSTEM_H

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

#endif //SAGARDOENGINE_ECS_ISYSTEM_H
