#ifndef SAGARDOENGINE_CAMERAUPDATESYSTEM_H
#define SAGARDOENGINE_CAMERAUPDATESYSTEM_H

#include "../ECS/include/SagardoEngine/ECS/ISystem.h"

namespace SagardoEngine
{
    class CameraUpdateSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, float deltaTime) override;
    };
} // SagardoEngine

#endif //SAGARDOENGINE_CAMERAUPDATESYSTEM_H