#ifndef RENDERER_H
#define RENDERER_H
#include "IRenderPipeline.h"

namespace SagardoEngine
{
    class RenderPipeline final : public IRenderPipeline
    {
    public:
        void Render() override;

    private:
        void Render2d() const;
        void Render3d() const;
    };
} // SagardoEngine

#endif //RENDERER_H
