#include "RendererSystem.h"

#include "Components.h"
#include "glad/glad.h"

namespace SagardoEngine
{
    void RendererSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world.system<
            const PositionComponent,
            const RotationEulerComponent,
            const ScaleComponent,
            const MeshComponent,
            const ShaderComponent,
            const TextureComponent>()
        .each([](
            const PositionComponent& position,
            const RotationEulerComponent& rotation,
            const ScaleComponent& scale,
            const MeshComponent& mesh,
            const ShaderComponent& shader,
            const TextureComponent& texture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.TextureId);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture.Texture0Id);
            
            glUseProgram(shader.ShaderProgramId);
            glBindVertexArray(mesh.VertexArrayObject);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        })
        .run(deltaTime);


    }
}