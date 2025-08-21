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
                const CameraComponent>("CameraUpdateSystem")
            .each([](
                const flecs::iter& it,
                const size_t index, 
                const PositionComponent& position,
                const RotationComponent& rotation,
                const CameraComponent& camera)
            {
                // --- Normalize quaternion (protect against drift) ---
                const auto rotationValue = glm::normalize(ComponentUtils::ToQuaternion(rotation));

                // --- View matrix as inverse(world transform) ---
                const auto R_inv = glm::mat4_cast(glm::conjugate(rotationValue));
                const auto T_inv = glm::translate(GlmUtils::Identity, -ComponentUtils::ToVector3(position));

                // --- Projection ---
                const auto fovy   = glm::radians(std::clamp(camera.Fov, 1.0f, 120.0f));
                const auto aspect = std::max(camera.AspectRatio, 1e-6f);
                const auto nearp  = std::max(camera.NearPlane, 1e-6f);
                const auto farp   = std::max(camera.FarPlane, nearp + 1e-3f);
                
                const auto projection =  glm::perspective(fovy, aspect, nearp, farp);
                const auto view = R_inv * T_inv;
                const auto viewPort = projection * view;
                
                it.world().set<CameraMatricesComponent>(
                {
                    .View = view,
                    .Projection = projection,
                    .Viewport = viewPort,
                });
            })
            .run(deltaTime);
    }
} 