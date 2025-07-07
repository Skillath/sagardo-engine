#ifndef COMPONENTUTILS_H
#define COMPONENTUTILS_H

#include "raylib.h"
#include "Components.h"

namespace SagardoEngine
{
    class ComponentUtils
    {
    public:
        static PositionComponent ToPositionComponent(const Vector3& position)
        {
            return PositionComponent
            {
                .X = position.x,
                .Y = position.y,
                .Z = position.z,
            };
        }

        static Vector3 ToVector3(const PositionComponent& position)
        {
            return Vector3
            {
                .x = position.X,
                .y = position.Y,
                .z = position.Z,
            };
        }

        static ScaleComponent ToScaleComponent(const Vector3& scale)
        {
            return ScaleComponent
            {
                .X = scale.x,
                .Y = scale.y,
                .Z = scale.z,
            };
        }

        static Vector3 ToVector3(const ScaleComponent& scale)
        {
            return Vector3
            {
                .x = scale.X,
                .y = scale.Y,
                .z = scale.Z,
            };
        }

        static RotationEulerComponent ToRotationEulerComponent(const Vector3& eulerAngles)
        {
            return RotationEulerComponent
            {
                .X = eulerAngles.x,
                .Y = eulerAngles.y,
                .Z = eulerAngles.z,
            };
        }

        static Vector3 ToVector3(const RotationEulerComponent& eulerAngles)
        {
            return Vector3
            {
                .x = eulerAngles.X,
                .y = eulerAngles.Y,
                .z = eulerAngles.Z,
            };
        }
    };
}

#endif //COMPONENTUTILS_H
