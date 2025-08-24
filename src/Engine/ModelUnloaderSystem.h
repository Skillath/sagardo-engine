#ifndef SAGARDOENGINE_MODELUNLOADERSYSTEM_H
#define SAGARDOENGINE_MODELUNLOADERSYSTEM_H

#include "ECS/ISystem.h"

namespace SagardoEngine
{
    class ModelUnloaderSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
    
}

#endif //SAGARDOENGINE_MODELUNLOADERSYSTEM_H
