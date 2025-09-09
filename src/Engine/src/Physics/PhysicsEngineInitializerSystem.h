#ifndef SAGARDOENGINE_PHYSICS_PHYSICSENGINEINITIALIZERSYSTEM_H
#define SAGARDOENGINE_PHYSICS_PHYSICSENGINEINITIALIZERSYSTEM_H

#include "SagardoEngine/ECS/ISystem.h"

namespace SagardoEngine::Physics
{
    class PhysicsEngineInitializerSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
}

#endif //SAGARDOENGINE_PHYSICS_PHYSICSENGINEINITIALIZERSYSTEM_H