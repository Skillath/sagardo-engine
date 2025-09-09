#include "RendererSystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SagardoEngine/Components.h"
#include "SagardoEngine/ComponentUtils.h"

namespace SagardoEngine
{
    void RendererSystem::Run(
        flecs::world& world,
        const float deltaTime)
    {
        world
            .system<
                const RotatorComponent,
                RotationComponent>()
            .each([](
                const flecs::iter& it,
                const size_t index,
                const RotatorComponent& rotator,
                RotationComponent& rotation)
                {
                    // convert to radians * deltaTime
                    const auto deltaRad = glm::radians(rotator.RotationSpeed) * it.delta_time();

                    // build delta quaternion from Euler delta
                    const auto dq = glm::quat(deltaRad); // ctor takes radians

                    // accumulate: apply delta after current orientation
                    const auto result = glm::normalize(ComponentUtils::ToQuaternion(rotation) * dq);

                    rotation.W = result.w;
                    rotation.X = result.x;
                    rotation.Y = result.y;
                    rotation.Z = result.z;
                })
            .run(deltaTime);
        
        
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
                
                const auto viewMatrix = *it.world().get<CameraMatricesComponent>();

                const auto t = glm::translate(GlmUtils::Identity, ComponentUtils::ToVector3(position));
                const auto r = glm::mat4_cast(ComponentUtils::ToQuaternion(rotation)); 
                const auto s = glm::scale(GlmUtils::Identity, ComponentUtils::ToVector3(scale));
                
                const auto mat = t * r * s;	
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
