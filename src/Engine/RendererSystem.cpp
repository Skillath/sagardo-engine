#include "RendererSystem.h"

#include "Components.h"
#include "Shader.h"
#include "glad/gl.h"

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
        world
            .system<
                const PositionComponent,
                const RotationComponent,
                const ScaleComponent,
                const ModelComponent,
                const ShaderComponent>()
            .each([](
                const flecs::iter& it,
                const size_t index,
                const PositionComponent& position,
                const RotationComponent& rotation,
                const ScaleComponent& scale,
                const ModelComponent& model,
                const ShaderComponent& shader)
            {
                if (model.LoadedModel == nullptr)
                    return;
                
                const Shader shaderProgram(shader.ShaderProgramId);
                shaderProgram.Use();
                
                const auto viewMatrix = it.world().get<CameraMatricesComponent>();
                
                auto mat = GlmUtils::Identity;
                mat = glm::translate(mat, ComponentUtils::ToVector3(position)); // translate it down so it's at the center of the scene
                mat = glm::scale(mat, ComponentUtils::ToVector3(scale));	// it's a bit too big for our scene, so scale it down
                
                const auto projection = viewMatrix.Projection;
                const auto view = viewMatrix.View;
                
                shaderProgram.SetMat4("projection", projection);
                shaderProgram.SetMat4("view", view);
                shaderProgram.SetMat4("model", mat);

                model.LoadedModel->Draw(shaderProgram);
            })
            .run(deltaTime);
    }
}
