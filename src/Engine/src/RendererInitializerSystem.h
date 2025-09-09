#ifndef SAGARDOENGINE_RENDERERINITIALIZERSYSTEM_H
#define SAGARDOENGINE_RENDERERINITIALIZERSYSTEM_H

#include "SagardoEngine/ECS/ISystem.h"

namespace SagardoEngine
{
    class RendererInitializerSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
}

#endif //SAGARDOENGINE_RENDERERINITIALIZERSYSTEM_H
