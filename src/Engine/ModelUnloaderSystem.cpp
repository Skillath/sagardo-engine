#include "ModelUnloaderSystem.h"

#include "Components.h"
#include "glad/gl.h"

namespace SagardoEngine
{
    void ModelUnloaderSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world
            .system<
                const MeshComponent,
                const ShaderComponent,
                const TextureComponent>()
            .each([](
                const flecs::iter& it,
                const size_t index,
                const MeshComponent& mesh,
                const ShaderComponent& shader,
                const TextureComponent& texture)
                {
                    glDeleteVertexArrays(1, &mesh.VertexArrayObject);
                    glDeleteBuffers(1, &mesh.VertexBufferObject);
                    glDeleteBuffers(1, &mesh.ElementBufferObject);
                    glDeleteProgram(shader.ShaderProgramId);
                    glDeleteTextures(1, &texture.TextureId);

                    it.entity(index)
                        .remove<MeshComponent>()
                        .remove<ShaderComponent>()
                        .remove<TextureComponent>();
                })
            .run(deltaTime);
    }
}