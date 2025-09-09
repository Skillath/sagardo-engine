#include "SagardoEngine/GlTextureLoader.h"

#include <cstdio>

#include "stb_image.h"

namespace SagardoEngine
{
    GLTexture GlTextureLoader::CreateGlTexture(
        const std::byte* data,
        const unsigned int width,
        const unsigned int height,
        const bool isSrgb,
        const GLenum srcFmt)
    {
        GLTexture texture{};
        glGenTextures(1, &texture.Id);
        glBindTexture(GL_TEXTURE_2D, texture.Id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        GLenum internal = GL_RGBA8;
        if (srcFmt == GL_RED)
        {
            internal = GL_R8;
        }
        else if (srcFmt == GL_RGB)
        {
            internal = isSrgb
                ? GL_SRGB8
                : GL_RGB8;
        }
        else if (srcFmt == GL_RGBA)
        {
            internal = isSrgb
                ? GL_SRGB8_ALPHA8
                : GL_RGBA8;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, srcFmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        texture.Width = width;
        texture.Height = height;
        texture.Channels = (srcFmt == GL_RED ? 1 : (srcFmt == GL_RGB ? 3 : 4));
        return texture;
    }

    GLTexture GlTextureLoader::LoadTextureFromFile(
        const std::filesystem::path& path,
        const bool isSrgb)
    {
        int width = 0;
        int height = 0;
        int channels = 0;
        stbi_set_flip_vertically_on_load(true); // flip if your UVs expect it
        
        const auto pixels = (std::byte*)stbi_load(
            path.string().c_str(),
            &width,
            &height,
            &channels,
            0);

        if (pixels == nullptr)
        {
            std::fprintf(stderr, "stb_image: failed to load %s\n", path.string().c_str());
            std::exit(EXIT_FAILURE);
        }

        const GLenum src = channels == 1 ? GL_RED : (channels == 3 ? GL_RGB : GL_RGBA);
        const GLTexture texture = CreateGlTexture(pixels, width, height, isSrgb, src);
        
        stbi_image_free(pixels);

        return texture;
    }
}
