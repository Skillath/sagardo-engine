#include "CameraUpdateSystem.h"

#include "Components.h"
#include "ComponentUtils.h"

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
            .each([&world](
                const PositionComponent& position,
                const RotationComponent& rotation,
                const CameraComponent& camera)
            {
                const auto view = glm::lookAt(
                    ComponentUtils::ToVector3(position),
                    GlmUtils::Zero,
                    GlmUtils::Up);

                world.set(ViewMatrixComponent
                    {
                        .ViewMatrix = view
                    });
            })
            .run(deltaTime);
    }
} 