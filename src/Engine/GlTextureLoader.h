#ifndef SAGARDOENGINE_GLTEXTURELOADER_H
#define SAGARDOENGINE_GLTEXTURELOADER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <filesystem>

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
            unsigned int width,
            unsigned int height,
            bool isSrgb,
            GLenum srcFmt);

        static GLTexture LoadTextureFromFile(
            const std::filesystem::path& path,
            bool isSrgb); 
    };
}

#endif //SAGARDOENGINE_GLTEXTURELOADER_H