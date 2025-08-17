#include "GameObject.h"

#include <print>

#include "Components.h"
#include "ComponentUtils.h"

namespace SagardoEngine
{
    GameObject::GameObject(
        const std::string_view& name,
        const Ecs::World* world) :
        _entity(world->CreateEntity(name)),
        _name(name)
    {
        assert(world != nullptr);
        _world = world;
       
        _entity.AddComponent<PositionComponent>(
        {
            .X = 0,
            .Y = 0,
            .Z = 0,
        });

        _entity.AddComponent<ScaleComponent>(
        {
            .X = 1,
            .Y = 1,
            .Z = 1,
        });
        
        _entity.AddComponent<RotationComponent>(
        {
            .X = 0,
            .Y = 0,
            .Z = 0,
            .W = 1,
        });

        std::println("GameObject created {0}!", name);
    }

    GameObject::~GameObject()
    {
        std::println("GameObject Destroyed {0}!", _name);
    
        _entity.Destroy();
        _world = nullptr;
    }
}
