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

            shaderProgram.Use();

            glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 view          = glm::mat4(1.0f);
            glm::mat4 projection    = glm::mat4(1.0f);
            model = glm::rotate(model, (float)TimeProvider::GetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
            view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);
            
            // retrieve the matrix uniform locations
            unsigned int modelLoc = glGetUniformLocation(shaderProgram.GetId(), "model");
            unsigned int viewLoc  = glGetUniformLocation(shaderProgram.GetId(), "view");
            // pass them to the shaders (3 different ways)
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            shaderProgram.SetMat4("projection", projection);

            
            glBindVertexArray(mesh.VertexArrayObject);
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        })
        .run(deltaTime);
    }
}
