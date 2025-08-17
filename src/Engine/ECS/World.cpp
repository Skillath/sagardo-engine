#include <stdexcept>

#include "World.h"
#include "ISystem.h"

namespace SagardoEngine::Ecs
{
    World::~World()
    {
        _world.release();
    }

    Entity World::CreateEntity(const std::string_view& name) const
    {
        const auto entity = _world.entity();

        if (!name.empty())
        {
            entity.set_name(name.data());
        }
            
        return Entity
        {
            entity,
            _world,
            entity.name().c_str(),
        };
    }

    void World::DestroyEntity(const Entity& entity)
    {
        entity.Destroy();
    }

    void World::RunSystem(ISystem& system, const float deltaTime)
    {
        system.Run(_world, deltaTime);
    }

    void World::Update(const float deltaTime) const
    {
        if (!_world.progress(deltaTime))
            throw std::runtime_error("Scene update failed!");
    }
}