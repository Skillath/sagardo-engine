#ifndef FILE_H
#define FILE_H

#include <string>

namespace SagardoEngine::IO
{
    struct File
    {
        static std::string ReadFile(const std::string& path);
    };
}

#endif //FILE_H