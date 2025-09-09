#ifndef SAGARDOENGINE_GLMHELPER_H
#define SAGARDOENGINE_GLMHELPER_H

#include <iosfwd>
#include <glm/glm.hpp>

namespace SagardoEngine
{
    struct GlmUtils
    {
        static constexpr glm::vec3 Zero {0.0f, 0.0f, 0.0f};
        static constexpr glm::vec3 One {1.0f, 1.0f, 1.0f};
        static constexpr glm::vec3 Up {0.0f, 1.0f, 0.0f};
        static constexpr glm::vec3 Down {0.0f, -1.0f, 0.0f};
        static constexpr glm::vec3 Right {1.0f, 0.0f, 0.0f};
        static constexpr glm::vec3 Left {-1.0f, 0.0f, 0.0f};
        static constexpr glm::vec3 Forward {0.0f, 0.0f, 1.0f};
        static constexpr glm::vec3 Back {0.0f, 0.0f, -1.0f};

        static constexpr glm::mat4 Identity {1.0f};
        
        static std::ostream& PrintMat4(
            std::ostream& os,
            const glm::mat4& matrix,
            int width = 10,
            int prec = 3);
    };    
}



#endif //SAGARDOENGINE_GLMHELPER_H