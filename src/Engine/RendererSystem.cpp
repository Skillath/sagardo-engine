#include "RendererSystem.h"

#include "Components.h"
#include "Shader.h"
#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ComponentUtils.h"
#include "TimeProvider.h"

namespace SagardoEngine
{
    void RendererSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        world
            .system<
                const PositionComponent,
                const RotationComponent,
                const ScaleComponent,
                const MeshComponent,
                const ShaderComponent,
                const TextureComponent>()
            .each([&world](
                const PositionComponent& position,
                const RotationComponent& rotation,
                const ScaleComponent& scale,
                const MeshComponent& mesh,
                const ShaderComponent& shader,
                const TextureComponent& texture)
            {                
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture.TextureId);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture.Texture0Id);

                const Shader shaderProgram(shader.ShaderProgramId);
                shaderProgram.Use();


                auto model = GlmUtils::Identity;
                
                model = glm::rotate(model, (float)TimeProvider::GetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
                
                const auto projection = glm::perspective(glm::radians(60.0f), (float)1280 / (float)720, 0.1f, 100.0f);
                
                const auto viewMatrix = world.get<ViewMatrixComponent>();
                const auto view = viewMatrix.ViewMatrix;
                shaderProgram.SetMat4("model", model);
                shaderProgram.SetMat4("view", view);
                shaderProgram.SetMat4("projection", projection);
                
                glBindVertexArray(mesh.VertexArrayObject);
                
                glDrawArrays(GL_TRIANGLES, 0, 36);
            })
            .run(deltaTime);
    }
}
