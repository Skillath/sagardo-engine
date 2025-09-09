#ifndef SAGARDOENGINE_IO_FILE_H
#define SAGARDOENGINE_IO_FILE_H

#include <filesystem>
#include <string>

namespace SagardoEngine::IO
{
    struct File
    {
        static std::string ReadAllText(const std::filesystem::path& path);
        static std::byte* LoadAllBytes(const std::filesystem::path& path);
    };
}

#endif //SAGARDOENGINE_IO_FILE_H