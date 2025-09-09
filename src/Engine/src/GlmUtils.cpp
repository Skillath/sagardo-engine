#include "SagardoEngine/GlmUtils.h"

#include <iomanip>

namespace SagardoEngine
{
    std::ostream& GlmUtils::PrintMat4(
        std::ostream& os,
        const glm::mat4& matrix,
        const int width,
        const int prec)
    {
        os << std::fixed << std::setprecision(prec);
        for (int r = 0; r < 4; ++r) {
            os << '[';
            for (int c = 0; c < 4; ++c) {
                os << std::setw(width) << matrix[c][r]; // GLM: column-major, so [col][row]
                if (c < 3) os << ' ';
            }
            os << "]\n";
        }
        return os;
    }
}
