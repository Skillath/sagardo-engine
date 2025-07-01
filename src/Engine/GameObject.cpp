#include "GameObject.h"
#include "Components.h"
#include <print>

using namespace SagardoEngine;

GameObject::GameObject(const char* name, flecs::world* world)
{
    _name = name;
    _world = world;
    _entity = _world->entity(_name);
    _entity
        .set<PositionComponent>({0,0,0})
        .set<ScaleComponent>({1,1,1})
        .set<RotationEulerComponent>({0, 0, 0});

    std::println("Entity created {0}!", name);
}

GameObject::~GameObject()
{
    std::println("Entity Destroyed {0}!", _name);

    _entity.destruct();
    _name = nullptr;
    _world = nullptr;
}