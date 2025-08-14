#include "ModelUnloaderSystem.h"

#include "Components.h"
#include "glad/glad.h"

namespace SagardoEngine
{
    void ModelUnloaderSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world
            .system<
                const MeshComponent,
                const ShaderComponent>()
            .each([](
                const MeshComponent& mesh,
                const ShaderComponent& shader)
                {
                    glDeleteVertexArrays(1, &mesh.VAO);
                    glDeleteBuffers(1, &mesh.VBO);
                    glDeleteBuffers(1, &mesh.EBO);
                    glDeleteProgram(shader.ShaderProgram);
                })
            .run(deltaTime);
    }
}