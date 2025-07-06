#include "RendererSystem.h"
#include "Components.h"
#include "ComponentUtils.h"

#include <print>

using namespace SagardoEngine;

void RendererSystem::Run(flecs::world& world, float deltaTime)
{
    world
        .system<CameraRefComponent>()
        .each([world](CameraRefComponent& cameraRef)
        {
            UpdateCamera(&cameraRef.CameraRef, cameraRef.CameraRef.projection);
            
            BeginDrawing();
            {
                ClearBackground(RAYWHITE);
                BeginMode3D(cameraRef.CameraRef);
                {
                    world
                        .system<
                            const ModelComponent,
                            const PositionComponent,
                            const RotationEulerComponent,
                            const ScaleComponent>()
                        .each([](
                            const ModelComponent& modelComponent,
                            const PositionComponent& positionComponent,
                            const RotationEulerComponent& rotationComponent,
                            const ScaleComponent& scaleComponent)
                            {
                                DrawModelEx(
                                    modelComponent.LoadedModel,
                                    ComponentUtils::ToVector3(positionComponent),
                                    ComponentUtils::ToVector3(rotationComponent),
                                    0.f,
                                    ComponentUtils::ToVector3(scaleComponent),
                                    WHITE);
                            });
                }
                EndMode3D();
            }
            EndDrawing();
        });
}
