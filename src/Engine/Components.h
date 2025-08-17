#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <filesystem>

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

    struct ShaderModifyBoolComponent : ShaderModifyComponent<bool>
    {
    };

    struct ShaderModifyIntegerComponent : ShaderModifyComponent<int>
    {
    };

    struct ShaderModifyFloatComponent : ShaderModifyComponent<float>
    {
    };

    struct FileLoaderComponent
    {        
        const std::filesystem::path& Path;
    };

    struct TextureComponent
    {
        unsigned int TextureId;
        unsigned int Texture0Id;
    };

    struct TriangleComponent
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
    
}

#endif