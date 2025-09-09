#ifndef SAGARDOENGINE_RENDERERSYSTEM_H
#define SAGARDOENGINE_RENDERERSYSTEM_H

#include "SagardoEngine/ECS/ISystem.h"

namespace SagardoEngine
{
    class RendererSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
}

#endif //SAGARDOENGINE_RENDERERSYSTEM_H
