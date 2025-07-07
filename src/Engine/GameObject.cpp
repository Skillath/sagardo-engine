#include "GameObject.h"
#include "Components.h"
#include <print>

using namespace SagardoEngine;

GameObject::GameObject(
    const char *name,
    Ecs::World* world) : _entity(world->CreateEntity())
{
    _name = name;
    _world = world;
    
    _entity.AddComponent<PositionComponent>(
    {
        .X = 0,
        .Y = 0,
        .Z = 0,
    });

    _entity.AddComponent<ScaleComponent>(
    {
        .X = 0.1,
        .Y = 0.1,
        .Z = 0.1,
    });

    _entity.AddComponent<RotationEulerComponent>(
    {
        .X = 0,
        .Y = 0,
        .Z = 0,
    });

    std::println("Entity created {0}!", name);
}

GameObject::~GameObject()
{
    std::println("Entity Destroyed {0}!", _name);
    
    _entity.Destroy();
    
    _name = nullptr;
    _world = nullptr;
}
