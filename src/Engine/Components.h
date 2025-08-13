#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <glm/glm.hpp>

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


    

    struct TriangleComponentOld
    {
    
        const char *VertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    
        const char *FragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        const float Vertices[12] =
        {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
           -0.5f, -0.5f, 0.0f,  // bottom left
           -0.5f,  0.5f, 0.0f   // top left 
       };
    
        const unsigned int Indices[6] =
        {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };    
    };

    struct TriangleComponent
    {    
        const char *VertexShaderSource;    
        const char *FragmentShaderSource;
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        const float* Vertices;
        unsigned int NumVertices;
        const unsigned int* Indices;
        unsigned int NumIndices;
    };
    
}

#endif