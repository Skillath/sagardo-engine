#include "RendererSystem.h"
#include "Components.h"
#include "ComponentUtils.h"
#include "raymath.h"
#include "rcamera.h"

using namespace SagardoEngine;

void RendererSystem::Run(flecs::world& world, const float deltaTime)
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
        .each([&camera](
            const ModelComponent& modelComponent,
            const PositionComponent& positionComponent,
            const RotationEulerComponent& rotationComponent,
            const ScaleComponent& scaleComponent)
            {
                for (int i = 0; i < modelComponent.LoadedModel.meshCount; i++)
                {
                    const auto& mesh = modelComponent.LoadedModel.meshes[i];
                    const auto materialIndex = modelComponent.LoadedModel.meshMaterial[i];
                    const auto& material = modelComponent.LoadedModel.materials[materialIndex];

                    Matrix transform = MatrixIdentity(); // Start with an identity matrix

                    // Apply transformations
                    transform = MatrixMultiply(transform, MatrixTranslate(positionComponent.X, positionComponent.Y, positionComponent.Z));
                    transform = MatrixMultiply(transform, MatrixRotateXYZ(Vector3{rotationComponent.X, rotationComponent.Y, rotationComponent.Z}));
                    transform = MatrixMultiply(transform, MatrixScale(scaleComponent.X, scaleComponent.Y, scaleComponent.Z));
                    
                    DrawMesh(mesh, material, transform);
                }
            });

    auto modelAnimateSystem = world
        .system<
            const ModelComponent,
            ModelAnimationComponent>()
        .multi_threaded(true)
        .each([](
            const ModelComponent& modelComponent,
            ModelAnimationComponent& modelAnimationComponent)
        {
            UpdateModelAnimation(
               modelComponent.LoadedModel,
               modelAnimationComponent.Animations[2],
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
