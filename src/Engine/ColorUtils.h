#ifndef COLORUTILS_H
#define COLORUTILS_H

#include "Color.h"
#include "Mathf.h"

namespace SagardoEngine
{
    struct ColorUtils final
    {        
        static Color32 ToColor32(const Color color)
        {
            constexpr unsigned char Min = 0;
            constexpr unsigned char Max = 255;
            
            const auto r = Mathf::Lerp(Min, Max, color.R);
            const auto g = Mathf::Lerp(Min, Max, color.G);
            const auto b = Mathf::Lerp(Min, Max, color.B);
            const auto a = Mathf::Lerp(Min, Max, color.A);
            return Color32(r, g, b, a);
            
        }
        
        static Color ToColor(const Color32 color) const
        {
            constexpr unsigned char Min = 0;
            constexpr unsigned char Max = 255;
            
            const auto r = Mathf::InverseLerp(Min, Max, color.R);
            const auto g = Mathf::InverseLerp(Min, Max, color.G);
            const auto b = Mathf::InverseLerp(Min, Max, color.B);
            const auto a = Mathf::InverseLerp(Min, Max, color.A);
            return Color(r, g, b, a);
        }
    };
}

#endif //COLORUTILS_H