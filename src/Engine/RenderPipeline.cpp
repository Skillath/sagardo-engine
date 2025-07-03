#include "RenderPipeline.h"

#include <raylib.h>

#include "Scene.h"

namespace SagardoEngine
{
    RenderPipeline::RenderPipeline(
        Scene* scene,
        CameraRefComponent* camera)
    {
        _scene=scene;
        _camera = camera;
    }

    void RenderPipeline::Render()
    {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            
            Render3d();
            Render2d();

            DrawFPS(0,0);
        }
        EndDrawing();
    }

    void RenderPipeline::Render2d() const
    {        
        // BeginMode2D(_camera->CameraRef);
        // {
        //     
        // }
        // EndMode2D();
    }

    void RenderPipeline::Render3d() const
    {
        BeginMode3D(_camera->CameraRef);
        {
            
        }
        EndMode3D();
    }
} // SagardoEngine