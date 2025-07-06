#ifndef RENDERERINITIALIZERSYSTEM_H
#define RENDERERINITIALIZERSYSTEM_H

#include "ISystem.h"

namespace SagardoEngine
{
    class RendererInitializerSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
}

#endif //RENDERERINITIALIZERSYSTEM_H
