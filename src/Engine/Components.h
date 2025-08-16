#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP


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
        const char* Path;
    };

    struct TextureComponent
    {
        unsigned int TextureId;
        unsigned int Texture0Id;
    };

    struct TriangleComponent
    {        
        const float* Vertices;
        unsigned int VerticesSize;
        const unsigned int* Indices;
        unsigned int IndicesSize;
        const char* FragmentShaderPath;
        const char* VertexShaderPath;
        const char* TexturePath;
        const float* TextCoords;
        unsigned int TextCoordsSize;
        int WrappingOptions;
        const char* AwesomeFaceTexturePath;
    };
    
}

#endif