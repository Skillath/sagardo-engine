#include "RendererInitializerSystem.h"

#include <print>
#include "Components.h"
#include "Entity.h"

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

                const Shader shaderProgram ("src/res/shaders/color.vert", "src/res/shaders/color.frag");
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
