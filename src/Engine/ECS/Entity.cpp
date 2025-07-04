#include "Entity.h"

#include <entt/entity/registry.hpp>

using namespace SagardoEngine::Ecs;

Entity::Entity(
    const char* name,
    const entt::entity& entityId,
    const entt::registry* world)
{
    _name = name;
    _entityId = entityId;
    _world = world;
}

Entity::~Entity()
{
}

void Entity::Destroy() const
{
    _world->destroy(_entityId);
}
