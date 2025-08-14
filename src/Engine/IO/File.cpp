#include "File.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace SagardoEngine::IO
{
    std::string File::ReadFile(const std::string& path)
    {
        std::ifstream in(path, std::ios::in | std::ios::binary);
        if (!in)
            throw std::runtime_error("Failed to open: " + path);
        
        std::ostringstream ss;
        ss << in.rdbuf();                  // read whole file
        return ss.str();  
    }
}