#ifndef SAGARDOENGINE_OPENGLDEBUG_H
#define SAGARDOENGINE_OPENGLDEBUG_H

#include "glad/gl.h"

namespace SagardoEngine::Debug
{    
    void GLAPIENTRY GlDebugOutput(
        GLenum source,
        GLenum type,
        unsigned int id,
        GLenum severity,
        GLsizei length,
        const char *message,
        const void *userParam);    
}

#endif //SAGARDOENGINE_OPENGLDEBUG_H