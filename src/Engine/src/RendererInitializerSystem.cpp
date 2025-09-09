#include "RendererInitializerSystem.h"

#include <print>
#include "SagardoEngine/Components.h"
#include "../ECS/include/SagardoEngine/ECS/Entity.h"

namespace SagardoEngine
{
    void RendererInitializerSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world
            .system<
                const FileLoaderComponent,
                ModelComponent>()
            .kind(flecs::OnStart)
            .each([](
                const flecs::iter& it,
                const size_t index,
                const FileLoaderComponent& fileLoaderComponent,
                ModelComponent& modelComponent)
            {
                const auto& entity = it.entity(index);
                modelComponent.LoadedModel = new Model(fileLoaderComponent.Path);

                const Shader shaderProgram ("res/shaders/unlit/unlit.vert", "res/shaders/unlit/unlit.frag");
                shaderProgram.Use();
                
                entity
                    .set<ShaderComponent>(
                    {
                       .ShaderProgramId = shaderProgram.GetId(), 
                    })
                    .remove<FileLoaderComponent>();
            })
            .run(deltaTime);
    }
}
