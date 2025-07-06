//
// Created by xabi on 7/07/25.
//

#include "../RendererInitializerSystem.h"
#include <print>
#include "Components.h"

using namespace SagardoEngine;

void RendererInitializerSystem::Run(flecs::world& world, float deltaTime)
{
    world
        .system<
            const CameraComponent,
            const PositionComponent>("CameraInitialization")
        .kind(flecs::OnStart)
        .each([](
            const flecs::entity entity,
            const CameraComponent &cameraComponent,
            const PositionComponent &position)
            {
                Camera camera;
                camera.position = {position.X, position.Y, position.Z};
                camera.fovy = cameraComponent.Fov;
                camera.target = cameraComponent.Target;
                camera.up = cameraComponent.Up;
                camera.projection = cameraComponent.Projection;
                entity.remove<CameraComponent>();
    
                entity.set<CameraRefComponent>(CameraRefComponent{ camera });
    
                std::println("Camera created!");
            });
    
    world
        .system<
            ModelComponent,
            ModelAnimationComponent,
            const FileLoaderComponent>("MeshRendererInitialization")
        .kind(flecs::OnStart)
        .each([](
            const flecs::entity entity,
            ModelComponent &modelComponent,
            ModelAnimationComponent &modelAnimationComponent,
            const FileLoaderComponent &meshRendererComponent)
        {
            char path[1024];
            strcpy(path, GetWorkingDirectory());
            strcat(path, meshRendererComponent.Path);
    
            auto model = LoadModel(path);
    
            modelComponent.LoadedModel = model;
            
            int animationsCount = 0;
            auto animations = LoadModelAnimations(path, &animationsCount);
    
            modelAnimationComponent.AnimationsCount = animationsCount;
            modelAnimationComponent.Animations = animations;
    
            entity.remove<FileLoaderComponent>();
        });
    
    if (!world.progress())
        throw std::runtime_error("Scene initialization failed!");
}
