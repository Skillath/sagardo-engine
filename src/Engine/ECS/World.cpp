//
// Created by xabi on 4/07/25.
//

#include "World.h"

using namespace SagardoEngine::Ecs;

Entity World::CreateEntity()
{
    const auto entity = _world.create();
            
    return Entity
    {
        entity
    };
}

void World::DestroyEntity(const Entity& entity)
{
    _world.destroy(entity._entityId);
}
