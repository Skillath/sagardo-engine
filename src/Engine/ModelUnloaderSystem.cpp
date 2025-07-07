//
// Created by xabi on 7/07/25.
//

#include "ModelUnloaderSystem.h"

#include <stdexcept>

#include "raylib.h"
#include "Components.h"

void SagardoEngine::ModelUnloaderSystem::Run(flecs::world& world, float deltaTime)
{
    world
        .system<const ModelComponent>()
        .each([](const ModelComponent &modelComponent)
        {
           UnloadModel(modelComponent.LoadedModel);
        })
        .run();
}
