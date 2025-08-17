#ifndef SHADER_H
#define SHADER_H

#include <filesystem>

#include "glad/glad.h"
#include <glm/glm.hpp>

#include <string>

namespace SagardoEngine
{
    class Shader
    {
    private:
        unsigned int _id;
    
    public:  
        Shader(
            const std::filesystem::path& vertexPath,
            const std::filesystem::path& fragmentPath);
        
        explicit Shader(unsigned int id);
        
        // use/activate the shader
        void Use() const;
        // utility uniform functions
        void SetBool(const std::string& name, bool value) const;  
        void SetInt(const std::string& name, int value) const;   
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string &name, const glm::vec2 &value) const;
        void SetVec2(const std::string &name, float x, float y) const;
        void SetVec3(const std::string &name, const glm::vec3 &value) const;
        void SetVec3(const std::string &name, float x, float y, float z) const;
        void SetVec4(const std::string &name, const glm::vec4 &value) const;
        void SetVec4(const std::string &name, float x, float y, float z, float w) const;
        void SetMat2(const std::string &name, const glm::mat2 &mat) const;
        void SetMat3(const std::string &name, const glm::mat3 &mat) const;
        void SetMat4(const std::string &name, const glm::mat4 &mat) const;

        [[nodiscard]] unsigned int GetId() const { return _id; }

    private:
        static void CheckCompileErrors(unsigned int shader, const std::string& type);
    };
}
#endif
