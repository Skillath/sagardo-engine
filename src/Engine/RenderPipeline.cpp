#include "RenderPipeline.h"

#include <raylib.h>

namespace SagardoEngine
{
    void RenderPipeline::Render()
    {
        BeginDrawing();
        {
            Render3d();
            Render2d();
        }
        EndDrawing();
    }

    void RenderPipeline::Render2d() const
    {        
        BeginMode2D();
        {
            
        }
        EndMode2D();
    }

    void RenderPipeline::Render3d() const
    {
        BeginMode3D();
        {
            
        }
        EndMode3D();
    }
} // SagardoEngine