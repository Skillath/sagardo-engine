#ifndef RENDERERSYSTEM_H
#define RENDERERSYSTEM_H

#include "ECS/ISystem.h"

namespace SagardoEngine
{
    class RendererSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, const float deltaTime) override;
    };
}

#endif //RENDERERSYSTEM_H
