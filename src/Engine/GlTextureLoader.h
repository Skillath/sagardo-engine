#ifndef GLTEXTURELOADER_H
#define GLTEXTURELOADER_H

#include <filesystem>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace SagardoEngine
{
    struct GLTexture
    {
        GLuint Id = 0;
        unsigned int Width = 0;
        unsigned int Height = 0;
        unsigned int Channels = 0;
    };
    
    struct GlTextureLoader
    {
        static GLTexture CreateGlTexture(
            const std::byte* data,
            const unsigned int width,
            const unsigned int height,
            const bool isSrgb,
            const GLenum srcFmt);

        static GLTexture LoadTextureFromFile(
            const std::filesystem::path& path,
            const bool isSrgb); 
    };
}

#endif //SAGARDOENGINE_GLTEXTURELOADER_H