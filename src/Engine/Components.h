#ifndef SAGARDOENGINE_COMPONENTS_HPP
#define SAGARDOENGINE_COMPONENTS_HPP

#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Color.h"
#include "GlmUtils.h"
#include "Model.h"

namespace SagardoEngine
{    
    struct TransformComponent
    {
    private:
        glm::mat4 Matrix = glm::mat4(1.0f);
        
    public:
        [[nodiscard]]
        glm::vec3 GetPosition() const
        {
            return glm::vec3(Matrix[3][0], Matrix[3][1], Matrix[3][2]);
        }

        void SetPosition(const float x, const float y, const float z)
        {
            Matrix[3][0] = x;
            Matrix[3][1] = y;
            Matrix[3][2] = z;
        }

        [[nodiscard]]
        glm::vec3 GetScale() const
        {
            return glm::vec3(Matrix[0][0], Matrix[0][1], Matrix[0][2]);
        }

        void SetScale(const float x, const float y, const float z)
        {
            Matrix[0][0] = x;
            Matrix[0][1] = y;
            Matrix[0][2] = z;
        }

        [[nodiscard]]
        glm::quat GetRotation() const
        {
            
        }

        void SetRotation(glm::quat rotation)
        {
            throw std::runtime_error("Not implemented");
        }
    };
    
    struct PositionComponent final
    {
        float X = 0.f;
        float Y = 0.f;
        float Z = 0.f;
    };

    struct ScaleComponent final
    {
        float X = 1.f;
        float Y = 1.f;
        float Z = 1.f;
    };
    
    struct RotationComponent final
    {
        float X = 0.f;
        float Y = 0.f;
        float Z = 0.f;
        float W = 1.f;
    };

    struct MeshComponent final
    {
        unsigned int VertexArrayObject;
        unsigned int VertexBufferObject;
        unsigned int ElementBufferObject;
    };

    struct ShaderComponent final
    {
        unsigned int ShaderProgramId;
    };

    struct ModelComponent final
    {
        Model* LoadedModel = nullptr;
    };

    struct FileLoaderComponent final
    {        
        std::filesystem::path Path;
    };

    struct TextureComponent final
    {
        unsigned int TextureId;
        unsigned int Texture0Id;
    };

    struct ModelLoaderComponent final
    {
        std::filesystem::path Path;
    };

    struct CameraComponent final
    {
        float Fov = 45.f;
        float NearPlane = 0.1f;
        float FarPlane = 100.0f;
        float AspectRatio = 16.f / 9.f;
        bool IsOrthographic = false;
    };

    struct ViewMatrixComponent final
    {
        glm::mat4 ViewMatrix;
    };

    struct CameraMatricesComponent final
    {
        glm::mat4 View = GlmUtils::Identity;
        glm::mat4 Projection = GlmUtils::Identity;
        glm::mat4 Viewport = GlmUtils::Identity;
    };

    struct ActiveCameraTag final
    {
        //This is a Tag
    };

    struct LightComponent final
    {
        float Red;
        float Green;
        float Blue;
        float LightIntensity;
    };
}

#endif