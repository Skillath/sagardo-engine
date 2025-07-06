//
// Created by xabi on 6/07/25.
//

#ifndef RENDERERSYSTEM_H
#define RENDERERSYSTEM_H

#include "ECS/ISystem.h"

namespace SagardoEngine
{
    class RendererSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
}


#endif //RENDERERSYSTEM_H
