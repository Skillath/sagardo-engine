//
// Created by xabi on 18/8/25.
//

#ifndef CAMERAUPDATESYSTEM_H
#define CAMERAUPDATESYSTEM_H
#include "ISystem.h"

namespace SagardoEngine
{
    class CameraUpdateSystem final : public Ecs::ISystem
    {
    public:
        void Run(flecs::world& world, const float deltaTime) override;
    };
} // SagardoEngine

#endif //CAMERAUPDATESYSTEM_H