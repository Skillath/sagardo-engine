#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "Shader.h"

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
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };

    struct ShaderComponent
    {
        unsigned int ShaderProgram;
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
        const float* TextCoords;
        const unsigned int TextCoordsSize;
        const int WrappingOptions;
    };

    struct TriangleComponent
    {        
        const float* Vertices;
        unsigned int VerticesSize;
        const unsigned int* Indices;
        unsigned int IndicesSize;
        const char* FragmentShaderPath;
        const char* VertexShaderPath;
    };
    
}

#endif