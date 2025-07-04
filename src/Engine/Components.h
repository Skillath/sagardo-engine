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

    static PositionComponent ToPositionComponent(this const Vector3& position)
    {
        return PositionComponent
        {
            .X = position.x,
            .Y = position.y,
            .Z = position.z,
        };
    }

    static Vector3 ToVector3(this const PositionComponent& position)
    {
        return Vector3
        {
            .x = position.X,
            .y = position.Y,
            .z = position.Z,
        };
    }

    static ScaleComponent ToScaleComponent(this const Vector3& position)
    {
        return ScaleComponent
        {
            .X = position.x,
            .Y = position.y,
            .Z = position.z,
        };
    }

    static Vector3 ToVector3(this const ScaleComponent& position)
    {
        return Vector3
        {
            .x = position.X,
            .y = position.Y,
            .z = position.Z,
        };
    }

    static RotationEulerComponent ToRotationEulerComponent(this const Vector3& position)
    {
        return RotationEulerComponent
        {
            .X = position.x,
            .Y = position.y,
            .Z = position.z,
        };
    }

    static Vector3 ToVector3(this const RotationEulerComponent& position)
    {
        return Vector3
        {
            .x = position.X,
            .y = position.Y,
            .z = position.Z,
        };
    }
}

#endif