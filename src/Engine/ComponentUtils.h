#ifndef COMPONENTUTILS_H
#define COMPONENTUTILS_H

#include "Components.h"
#include <glm/glm.hpp>

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

        static RotationEulerComponent ToRotationEulerComponent(const glm::vec3& eulerAngles)
        {
            return RotationEulerComponent
            {
                .X = eulerAngles.x,
                .Y = eulerAngles.y,
                .Z = eulerAngles.z,
            };
        }

        static glm::vec3 ToVector3(const RotationEulerComponent& eulerAngles)
        {
            return glm::vec3(
                eulerAngles.X,
                eulerAngles.Y,
                eulerAngles.Z);
        }
    };
}

#endif //COMPONENTUTILS_H
