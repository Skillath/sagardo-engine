#include <print>

#include "SagardoEngine/Scene.h"

#include "CameraUpdateSystem.h"
#include "SagardoEngine/Components.h"
#include "ModelUnloaderSystem.h"
#include "RendererSystem.h"
#include "RendererInitializerSystem.h"

namespace SagardoEngine
{
    Scene::Scene(const std::string_view& name) :
        _name(name),
        _world(Ecs::World())
    {
        std::println("New Scene created {0}!", name);

        _world
            .GetInnerWorld()
            .prefab<GameObject>()
            .set<PositionComponent>(
            {
                .X = 0,
                .Y = 0,
                .Z = 0,
            })
            .set<RotationComponent>(
            {
                .X = 0,
                .Y = 0,
                .Z = 0,
                .W = 1,
            })
            .set<ScaleComponent>(
            {
                .X = 1,
                .Y = 1,
                .Z = 1,
            });
    }

    Scene::~Scene()
    {
        for (const auto gameObject : _gameObjects)
        {
            delete gameObject;
        }

        _gameObjects.clear();

        std::println("New Scene deleted {0}!", _name);
    }

    void Scene::Start()
    {
        RendererInitializerSystem rendererSystem { };
        _world.RunSystem(rendererSystem, 0);
    }

    GameObject* Scene::NewGameObject(const char *name)
    {
        const auto gameObject = new GameObject(name, _world);
        _gameObjects.push_back(gameObject);
        return gameObject;
    }

    bool Scene::TryRemoveGameObject(const GameObject *gameObject)
    {
        assert(gameObject != nullptr);
    
        const auto foundItem = std::ranges::find(_gameObjects, gameObject);
        if (foundItem == _gameObjects.end())
            return false;

        _gameObjects.erase(foundItem);
    
        delete *foundItem.base();

        return true;
    }

    void Scene::Update(const float deltaTime)
    {
        CameraUpdateSystem cameraUpdateSystem { };
        RendererSystem rendererSystem { };
        
        _world
            .RunSystem(cameraUpdateSystem, deltaTime)
            .RunSystem(rendererSystem, deltaTime);
    }

    void Scene::Stop()
    {
        ModelUnloaderSystem modelUnloadSystem { };
        _world.RunSystem(modelUnloadSystem, 0);
    }
}
