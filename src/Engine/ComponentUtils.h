#ifndef SAGARDOENGINE_COMPONENTUTILS_H
#define SAGARDOENGINE_COMPONENTUTILS_H

#include "Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SagardoEngine
{
    struct ComponentUtils
    {
        static PositionComponent ToPositionComponent(const glm::vec3& position);
        static glm::vec3 ToVector3(const PositionComponent& position);
        static ScaleComponent ToScaleComponent(const glm::vec3& scale);
        static glm::vec3 ToVector3(const ScaleComponent& scale);
        static glm::quat ToQuaternion(const RotationComponent& rotation);
        static RotationComponent ToRotationComponent(const glm::quat& rotation);
        static RotationComponent IdentityRotationComponent();

        static glm::mat4 ToModelMatrix(
            const PositionComponent& positionComponent,
            const RotationComponent& rotationComponent,
            const ScaleComponent& scaleComponent);

        static glm::quat EulerXYZDegToQuat(
            float x,
            float y,
            float z);
    };
}

#endif //SAGARDOENGINE_COMPONENTUTILS_H
