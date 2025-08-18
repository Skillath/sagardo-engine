#include <print>

#include "Scene.h"

#include "CameraUpdateSystem.h"
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
        const auto gameObject = new GameObject(name, &_world);
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
        _world.RunSystem(cameraUpdateSystem, deltaTime);
        
        RendererSystem rendererSystem { };
        _world.RunSystem(rendererSystem, deltaTime);
    }

    void Scene::Stop()
    {
        ModelUnloaderSystem modelUnloadSystem { };
        _world.RunSystem(modelUnloadSystem, 0);
    }
}