#ifndef RENDERER_H
#define RENDERER_H

#include "Components.h"
#include "IRenderPipeline.h"
#include "Scene.h"

namespace SagardoEngine
{
    class RenderPipeline final : public IRenderPipeline
    {
    private:
        CameraRefComponent* _camera;
        Scene* _scene;

    public:
        RenderPipeline(Scene* scene, CameraRefComponent* camera);
        void Render() override;

    private:
        void Render2d() const;
        void Render3d() const;
    };
} // SagardoEngine

#endif //RENDERER_H
