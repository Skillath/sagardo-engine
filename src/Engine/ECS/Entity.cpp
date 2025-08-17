#include "Entity.h"

#include <print>

namespace SagardoEngine::Ecs
{
    Entity::Entity(
        const flecs::entity& entityId,
        const flecs::world& world,
        const std::string_view& name) :
        _name(name),
        _world(world),
        _entityId(entityId)
    {
        if (world == nullptr)
            throw std::invalid_argument("world is null");

        std::println("Entity created: {0}", std::to_string(entityId));
    }

    Entity::~Entity()
    {
        Destroy();
    }

    void Entity::Destroy() const
    {    
        _entityId.destruct();
        std::println("Entity destroyed: {0}", std::to_string(_entityId));
    }
}