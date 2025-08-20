#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <filesystem>
#include <glm/glm.hpp>

#include "GlmUtils.h"
#include <glm/gtc/quaternion.hpp>

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
    
    struct RotationComponent
    {
        float X;
        float Y;
        float Z;
        float W;
    };

    struct MeshComponent
    {
        unsigned int VertexArrayObject;
        unsigned int VertexBufferObject;
        unsigned int ElementBufferObject;
    };

    struct ShaderComponent
    {
        unsigned int ShaderProgramId;
    };

    template<typename T>
    struct ShaderModifyComponent
    {
        const unsigned int ShaderProgram;
        const char* Name;
        const T Value;
    };

    struct ShaderModifyBoolComponent final : ShaderModifyComponent<bool>
    {
    };

    struct ShaderModifyIntegerComponent final : ShaderModifyComponent<int>
    {
    };

    struct ShaderModifyFloatComponent final : ShaderModifyComponent<float>
    {
    };

    struct FileLoaderComponent
    {        
        const std::filesystem::path& Path;
    };

    struct TextureComponent final
    {
        unsigned int TextureId;
        unsigned int Texture0Id;
    };

    struct TriangleComponent final
    {        
        const float* Vertices;
        const unsigned int* Indices;
        const float* TextCoords;
        unsigned int VerticesSize;
        unsigned int IndicesSize;
        unsigned int TextCoordsSize;
        int WrappingOptions;
        std::filesystem::path FragmentShaderPath;
        std::filesystem::path VertexShaderPath;
        std::filesystem::path TexturePath;
        std::filesystem::path AwesomeFaceTexturePath;
    };

    struct CameraComponent final
    {
        unsigned int Fov;
        float NearPlane;
        float FarPlane;
        bool IsOrthographic;
    };

    struct ViewMatrixComponent final
    {
        glm::mat4 ViewMatrix;
    };
    
}

#endif