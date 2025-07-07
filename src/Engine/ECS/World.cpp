#include "World.h"

#include <stdexcept>

#include "ISystem.h"

using namespace SagardoEngine::Ecs;

World::~World()
{
    _world.release();
}

Entity World::CreateEntity()
{
    const auto entity = _world.entity();
            
    return Entity
    {
        entity,
        &_world,
    };
}

void World::DestroyEntity(const Entity& entity)
{
    entity.Destroy();
}

void World::RunSystem(ISystem& system, float deltaTime)
{
    system.Run(_world, deltaTime);
}

void World::Update(const float deltaTime) const
{
    if (!_world.progress(deltaTime))
        throw std::runtime_error("Scene update failed!");
}
