#ifndef SHADER_H
#define SHADER_H
  
#include <string>
#include <fstream>

namespace SagardoEngine
{
    class Shader
    {
    private:
        unsigned int _id;
    
    public:  
        // constructor reads and builds the shader
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
        // use/activate the shader
        void Use() const;
        // utility uniform functions
        void SetBool(const std::string& name, bool value) const;  
        void SetInt(const std::string& name, int value) const;   
        void SetFloat(const std::string& name, float value) const;

        [[nodiscard]] unsigned int GetId() const { return _id; }

    private:
        static void CheckCompileErrors(unsigned int shader, const std::string& type);
    };
}
#endif
