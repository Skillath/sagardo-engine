#ifndef MODELUNLOADERSYSTEM_H
#define MODELUNLOADERSYSTEM_H

#include "ECS/ISystem.h"

namespace SagardoEngine
{
    class ModelUnloaderSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
    
}

#endif //MODELUNLOADERSYSTEM_H
