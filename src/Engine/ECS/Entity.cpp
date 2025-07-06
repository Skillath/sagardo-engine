#include "Entity.h"

#include <entt/entity/registry.hpp>

using namespace SagardoEngine::Ecs;

Entity::Entity(
    const entt::entity entityId,
    entt::registry* world)
    : _entityId(entityId)
{
    if (world == nullptr)
        throw std::invalid_argument("world is null");
    
    _world = world;
}

Entity::~Entity()
{
    Destroy();
    _world = nullptr;
}

void Entity::Destroy() const
{
    if (!_world->valid(_entityId))
        return;
    
    _world->destroy(_entityId);
}
