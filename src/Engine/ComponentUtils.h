#ifndef COMPONENTUTILS_H
#define COMPONENTUTILS_H

#include "Components.h"
#include <glm/glm.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SagardoEngine
{
    struct ComponentUtils
    {
        static PositionComponent ToPositionComponent(const glm::vec3& position)
        {
            return PositionComponent
            {
                .X = position.x,
                .Y = position.y,
                .Z = position.z,
            };
        }

        static glm::vec3 ToVector3(const PositionComponent& position)
        {
            return glm::vec3(
                position.X,
                position.Y,
                position.Z);
        }

        static ScaleComponent ToScaleComponent(const glm::vec3& scale)
        {
            return ScaleComponent
            {
                .X = scale.x,
                .Y = scale.y,
                .Z = scale.z,
            };
        }

        static glm::vec3 ToVector3(const ScaleComponent& scale)
        {
            return glm::vec3(
                scale.X,
                scale.Y,
                scale.Z);
        }

        
        static glm::quat ToQuaternion(const RotationComponent& rotation)
        {
            return glm::quat(
                rotation.W,
                rotation.X,
                rotation.Y,
                rotation.Z);
        }

        static RotationComponent ToRotationComponent(const glm::quat& rotation)
        {
            return RotationComponent
            {
                .X = rotation.x,
                .Y = rotation.y,
                .Z = rotation.z,
                .W = rotation.w,
            };
        }

        static RotationComponent IdentityRotationComponent()
        {
            return ToRotationComponent(glm::identity<glm::quat>());
        }

        static glm::mat4 ToModelMatrix(
            const PositionComponent& positionComponent,
            const RotationComponent& rotationComponent,
            const ScaleComponent& scaleComponent)
        {
            const auto T = glm::translate(glm::mat4(1.f), ToVector3(positionComponent));
            const auto R = glm::mat4_cast(ToQuaternion(rotationComponent));
            const auto S = glm::scale(glm::mat4(1.f), ToVector3(scaleComponent));
            
            return T * R * S; 
        }

        static glm::quat EulerXYZDegToQuat(
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
    };
}

#endif //COMPONENTUTILS_H
