#ifndef WORLD_H
#define WORLD_H

#include <entt/entt.hpp>

#include "Entity.h"

namespace SagardoEngine::Ecs
{       
    class World
    {
    private:
        entt::registry _world;
    
    public:
        Entity CreateEntity();
        static void DestroyEntity(const Entity& entity);
    };

}

#endif //WORLD_H
