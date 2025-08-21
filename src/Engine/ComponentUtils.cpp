#include "ComponentUtils.h"

namespace SagardoEngine
{
    PositionComponent ComponentUtils::ToPositionComponent(const glm::vec3& position)
    {
        return PositionComponent
        {
            .X = position.x,
            .Y = position.y,
            .Z = position.z,
        };
    }

    glm::vec3 ComponentUtils::ToVector3(const PositionComponent& position)
    {
        return glm::vec3(
            position.X,
            position.Y,
            position.Z);
    }

    ScaleComponent ComponentUtils::ToScaleComponent(const glm::vec3& scale)
    {
        return ScaleComponent
        {
            .X = scale.x,
            .Y = scale.y,
            .Z = scale.z,
        };
    }

    glm::vec3 ComponentUtils::ToVector3(const ScaleComponent& scale)
    {
        return glm::vec3(
            scale.X,
            scale.Y,
            scale.Z);
    }

    
    glm::quat ComponentUtils::ToQuaternion(const RotationComponent& rotation)
    {
        return glm::quat(
            rotation.W,
            rotation.X,
            rotation.Y,
            rotation.Z);
    }

    RotationComponent ComponentUtils::ToRotationComponent(const glm::quat& rotation)
    {
        return RotationComponent
        {
            .X = rotation.x,
            .Y = rotation.y,
            .Z = rotation.z,
            .W = rotation.w,
        };
    }

    RotationComponent ComponentUtils::IdentityRotationComponent()
    {
        return ToRotationComponent(glm::identity<glm::quat>());
    }

    glm::mat4 ComponentUtils::ToModelMatrix(
        const PositionComponent& positionComponent,
        const RotationComponent& rotationComponent,
        const ScaleComponent& scaleComponent)
    {
        const auto T = glm::translate(glm::mat4(1.f), ToVector3(positionComponent));
        const auto R = glm::mat4_cast(ToQuaternion(rotationComponent));
        const auto S = glm::scale(glm::mat4(1.f), ToVector3(scaleComponent));
        
        return T * R * S; 
    }

    glm::quat ComponentUtils::EulerXYZDegToQuat(
        const float x,
        const float y,
        const float z)
    {
        const auto r = glm::radians(glm::vec3{x, y, z});
        const auto qx = glm::angleAxis(r.x, glm::vec3{1.f,0.f,0.f});
        const auto qy = glm::angleAxis(r.y, glm::vec3{0.f,1.f,0.f});
        const auto qz = glm::angleAxis(r.z, glm::vec3{0.f,0.f,1.f});
        return glm::normalize(qz * qy * qx); // X then Y then Z
    }
}