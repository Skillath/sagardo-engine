#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "raylib.h"

namespace Engine
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

    struct MeshLoaderComponent
    {
        const char* Path;
    };

    struct MeshComponent
    {
        Mesh LoadedMesh;
    };

    struct ModelLoaderComponent
    {
        const char* Path;
    };

    struct ModelComponent
    {
        Model LoadedModel;
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
}

#endif