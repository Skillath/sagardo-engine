#include "CameraUpdateSystem.h"

#include "Components.h"

namespace SagardoEngine
{
    void CameraUpdateSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world
            .system<
                const PositionComponent,
                const RotationComponent,
                const CameraComponent>()
            .each([](
                const PositionComponent& position,
                const RotationComponent& rotation,
                const CameraComponent& camera)
            {
                
            })
            .run(deltaTime);
    }
} 