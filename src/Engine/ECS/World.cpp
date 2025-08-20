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
        return InitializeEntity(entity, _world, name);
    }

    void World::DestroyEntity(const Entity& entity)
    {
        entity.Destroy();
    }

    World& World::RunSystem(
        ISystem& system,
        const float deltaTime)
    {
        system.Run(_world, deltaTime);
        return *this;
    }

    Entity World::InitializeEntity(
        const flecs::entity& entity,
        const flecs::world& world,
        const std::string_view& name)
    {
        if (!name.empty())
        {
            entity.set_name(name.data());
        }
            
        return Entity
        {
            entity,
            world,
            entity.name().c_str(),
        };            
    }
}
