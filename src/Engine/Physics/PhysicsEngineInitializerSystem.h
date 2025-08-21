#ifndef PHYSICSENGINEINITIALIZERSYSTEM_H
#define PHYSICSENGINEINITIALIZERSYSTEM_H
#include "ISystem.h"

namespace SagardoEngine::Physics
{
    class PhysicsEngineInitializerSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
}

#endif //PHYSICSENGINEINITIALIZERSYSTEM_H