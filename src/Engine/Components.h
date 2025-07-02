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
}

#endif