//
// Created by xabi on 4/07/25.
//

#include "World.h"

using namespace SagardoEngine::Ecs;

Entity World::CreateEntity()
{
    const auto entity = _world.create();
            
    return Entity(entity, &_world);
}

void World::DestroyEntity(const Entity& entity)
{
    entity.Destroy();
}
