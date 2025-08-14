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
            const ShaderComponent>()
        .each([](
            const PositionComponent& position,
            const RotationEulerComponent& rotation,
            const ScaleComponent& scale,
            const MeshComponent& mesh,
            const ShaderComponent& shader)
        {
            // draw our first triangle
            glUseProgram(shader.ShaderProgram);
            glBindVertexArray(mesh.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            // glBindVertexArray(0); // no need to unbind it every time 
        })
        .run(deltaTime);


    }
}