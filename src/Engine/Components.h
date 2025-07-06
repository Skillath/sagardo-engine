#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "raylib.h"

namespace SagardoEngine
{   
    
    struct PositionComponent
    {
        float X;
        float Y;
        float Z;
    };

    struct ScaleComponent
    {
        float X;
        float Y;
        float Z;
    };
    
    struct RotationEulerComponent
    {
        float X;
        float Y;
        float Z;
    };

    struct MeshComponent
    {
        Mesh LoadedMesh;
    };

    struct ModelComponent
    {
        Model LoadedModel;
    };

    struct ModelAnimationComponent
    {
        int AnimationsCount;
        ModelAnimation* Animations;
    };

    struct CameraComponent
    {
        float Fov;
        Vector3 Target;
        Vector3 Up;
        CameraProjection Projection;
    };

    struct CameraRefComponent
    {
        Camera CameraRef;
    };

    struct FileLoaderComponent
    {
        const char* Path;
    };

    //Extension Methods
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
}

#endif