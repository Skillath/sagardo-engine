#include "SagardoEngine/GameObject.h"

#include <print>

#include "SagardoEngine/Components.h"

namespace SagardoEngine
{
    GameObject::GameObject(
        const std::string_view& name,
        const Ecs::World& world) :
        _world(world),
        _entity(world.CreateArchetype<GameObject>(name)),
        _name(name)
    {        
        std::println("GameObject created {0}!", name);
    }

    GameObject::~GameObject()
    {
        std::println("GameObject Destroyed {0}!", _name);
    
        _entity.Destroy();
    }
}
