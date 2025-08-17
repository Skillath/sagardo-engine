#include "RendererSystem.h"

#include <iostream>
#include <print>

#include "Components.h"
#include "Shader.h"
#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ComponentUtils.h"
#include "GlmUtils.h"


namespace SagardoEngine
{
    void RendererSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world.system<
            const PositionComponent,
            const RotationComponent,
            const ScaleComponent,
            const MeshComponent,
            const ShaderComponent,
            const TextureComponent>()
        .each([](
            const flecs::entity entity,
            const PositionComponent& position,
            const RotationComponent& rotation,
            const ScaleComponent& scale,
            const MeshComponent& mesh,
            const ShaderComponent& shader,
            const TextureComponent& texture)
        {            
            const Shader shaderProgram(shader.ShaderProgramId);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.TextureId);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture.Texture0Id);
            
            const auto transform = ComponentUtils::ToModelMatrix(
                position,
                rotation,
                scale);
            
            std::println("Running RenderSystem for entity {0}",
                entity.name().c_str());
            
             GlmUtils::PrintMat4(std::cout, transform);
            
            shaderProgram.Use();
            shaderProgram.SetMat4("transform", transform);
            
            glBindVertexArray(mesh.VertexArrayObject);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        })
        .run(deltaTime);
    }
}
