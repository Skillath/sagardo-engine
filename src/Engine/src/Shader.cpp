#include "SagardoEngine/Shader.h"

#include <iostream>

#include "SagardoEngine/IO/File.h"

namespace SagardoEngine
{
    Shader::Shader(
        const std::filesystem::path& vertexPath,
        const std::filesystem::path& fragmentPath,
        const std::filesystem::path& geometryPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        try
        {
            vertexCode = IO::File::ReadAllText(vertexPath);
            fragmentCode = IO::File::ReadAllText(fragmentPath);
            if (!geometryPath.empty())
            {
                geometryCode = IO::File::ReadAllText(geometryPath);
            }
            
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            return;
        }

        // shader Program
        _id = glCreateProgram();
    
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        
        const unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        glAttachShader(_id, vertex);
        // fragment Shader
        const unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
        glAttachShader(_id, fragment);

        unsigned int geometry = 0;
        if(!geometryPath.empty())
        {
            const char * gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            CheckCompileErrors(geometry, "GEOMETRY");
            glAttachShader(_id, geometry);
        }
        
        glLinkProgram(_id);
        
        CheckCompileErrors(_id, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(!geometryPath.empty())
        {
            glDeleteShader(geometry);
        }
        
    }

    Shader::Shader(const unsigned int id)
    {
        assert(glIsProgram(id));
        _id = id;
    }

    void Shader::Use() const
    {
        glUseProgram(_id);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void Shader::SetBool(const std::string& name, const bool value) const
    {         
        glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void Shader::SetInt(const std::string& name, const int value) const
    { 
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void Shader::SetFloat(const std::string& name, const float value) const
    { 
        glUniform1f(glGetUniformLocation(_id, name.c_str()), value); 
    }

    void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]); 
    }
    void Shader::SetVec2(
        const std::string &name,
        const float x,
        const float y) const
    { 
        glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]); 
    }
    void Shader::SetVec3(
        const std::string &name,
        const float x,
        const float y,
        const float z) const
    { 
        glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]); 
    }
    void Shader::SetVec4(
        const std::string &name,
        const float x,
        const float y,
        const float z,
        const float w) const
    { 
        glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::CheckCompileErrors(const unsigned int shader, const std::string& type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}
