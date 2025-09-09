#include "../include/SagardoEngine/IO/File.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace SagardoEngine::IO
{
    std::string File::ReadAllText(const std::filesystem::path& path)
    {
        std::string data;
        std::ifstream fileToRead;
        fileToRead.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try 
        {
            // open files
            fileToRead.open(path.string());
            
            std::stringstream stream;
            // read file's buffer contents into streams
            stream << fileToRead.rdbuf();
            // close file handlers
            fileToRead.close();
            // convert stream into string
            data = stream.str();

            stream.clear();
        }
        catch (std::ifstream::failure& e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw e;
        }
        
        return data;  
    }

    std::byte* File::LoadAllBytes(const std::filesystem::path& path)
    {
        throw std::runtime_error("Not implemented");
    }
}
