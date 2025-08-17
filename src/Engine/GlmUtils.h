//
// Created by xabi on 17/8/25.
//

#ifndef GLMHELPER_H
#define GLMHELPER_H

#include <iosfwd>
#include <glm/glm.hpp>

namespace SagardoEngine
{
    struct GlmUtils
    {
        static std::ostream& PrintMat4(
            std::ostream& os,
            const glm::mat4& matrix,
            const int width = 10,
            const int prec = 3);
    };    
}



#endif GLMHELPER_H