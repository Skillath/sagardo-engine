//
// Created by xabi on 21/8/25.
//

#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>

namespace SagardoEngine
{
    struct Color32 final
    {       
        unsigned char R;
        unsigned char G;
        unsigned char B;
        unsigned char A;

        constexpr Color32(
            const unsigned char r,
            const unsigned char g,
            const unsigned char b,
            const unsigned char a = 255) :
            R(r),
            G(g),
            B(b),
            A(a)
        {
            
        }

        explicit Color32(const glm::vec3 color) : Color32(color.r, color.g, color.b, 255)
        {
            
        }

        explicit Color32(const glm::vec4 color) : Color32(color.r, color.g, color.b, color.a)
        {
            
        }
    };

    struct Color final
    {        
        float R;
        float G;
        float B;
        float A;

        constexpr Color(
            const float r,
            const float g,
            const float b,
            const float a = 1.0f) :
            R(glm::clamp(0.0f, 1.0f, r)),
            G(glm::clamp(0.0f, 1.0f, g)),
            B(glm::clamp(0.0f, 1.0f, b)),
            A(glm::clamp(0.0f, 1.0f, a))
        {
        }

        explicit Color(const glm::vec3 color) : Color(color.r, color.g, color.b, 1.f)
        {
            
        }

        explicit Color(const glm::vec4 color) : Color(color.r, color.g, color.b, color.a)
        {
            
        }
    };

    struct Colors32 final
    {
        static constexpr Color32 Black { 0, 0, 0};
        static constexpr Color32 White { 1, 1, 1};
        static constexpr Color32 Red { 1, 0, 0};
        static constexpr Color32 Green { 0, 1, 0};
        static constexpr Color32 Blue { 0, 0, 1};
        static constexpr Color32 Yellow { 1, 1, 0};
        static constexpr Color32 Magenta { 1, 0, 1};
        static constexpr Color32 Cyan { 0, 1, 1};
        static constexpr Color32 Orange { 1, 0, 0 };
        static constexpr Color32 Purple { 0, 1, 0 };
    };

    struct Colors final
    {
        static constexpr Color Black { 0.f, 0.f, 0.f};
        static constexpr Color White { 1.f, 1.f, 1.f};
        static constexpr Color Red { 1, 0, 0};
        static constexpr Color Green { 0, 1, 0};
        static constexpr Color Blue { 0, 0, 1};
        static constexpr Color Yellow { 1, 1, 0};
        static constexpr Color Magenta { 1, 0, 1};
        static constexpr Color Cyan { 0, 1, 1};
        static constexpr Color Orange { 1, 0, 0 };
        static constexpr Color Purple { 0, 1, 0 };
    };
}


#endif //SAGARDOENGINE_COLOR_H