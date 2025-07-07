#include "RendererSystem.h"
#include "Components.h"
#include "ComponentUtils.h"

#include <print>

using namespace SagardoEngine;

void RendererSystem::Run(flecs::world& world, float deltaTime)
{
    Camera camera;

    auto updateCameraSystem = world
        .system<CameraRefComponent>()
        .each([&camera](CameraRefComponent& cameraRef)
        {
            UpdateCamera(&cameraRef.CameraRef, cameraRef.CameraRef.projection);
            camera = cameraRef.CameraRef;
        });
    
    updateCameraSystem.run(deltaTime);

    auto modelDrawSystem = world
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

    auto modelAnimateSystem = world
        .system<
            const ModelComponent,
            ModelAnimationComponent>()
        .each([](
            const ModelComponent& modelComponent,
            ModelAnimationComponent& modelAnimationComponent)
        {
            UpdateModelAnimation(
               modelComponent.LoadedModel,
               modelAnimationComponent.Animations[0],
               ++modelAnimationComponent.CurrentFrame); 
        });
    
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
        {
            modelDrawSystem.run(deltaTime);
            modelAnimateSystem.run(deltaTime);
        }
        EndMode3D();
    }
    EndDrawing();
}
