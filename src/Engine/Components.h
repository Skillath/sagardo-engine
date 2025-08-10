#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <glm/glm.hpp>

namespace SagardoEngine
{   
    struct TransformComponent
    {
        glm::mat4x4 Transform;
    };
    
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
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };

    struct ModelAnimationComponent
    {
        int AnimationsCount;
        int CurrentFrame;
    };

    struct CameraComponent
    {
        float Fov;
        glm::vec3 Target;
        glm::vec3 Up;
        
    };

    struct FileLoaderComponent
    {
        const char* Path;
    };

    struct RendererComponent
    {
        bool RenderToTexture = false;
    };
    
}

#endif