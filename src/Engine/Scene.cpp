#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
#include <algorithm>
#include <iostream>
#include <raylib.h>
#include <print>
#include <string>

using namespace SagardoEngine;

Scene::Scene(const char *name)
{
    _name = name;
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
    _name = nullptr;

}

void Scene::Start()
{
    _world
        .system<
            const CameraComponent,
            const PositionComponent>("CameraInitialization")
        .kind(flecs::OnStart)
        .each([](
            const flecs::entity entity,
            const CameraComponent &cameraComponent,
            const PositionComponent &position)
            {
                Camera camera;
                camera.position = {position.X, position.Y, position.Z};
                camera.fovy = cameraComponent.Fov;
                camera.target = cameraComponent.Target;
                camera.up = cameraComponent.Up;
                camera.projection = cameraComponent.Projection;
                entity.remove<CameraComponent>();

                entity.set<CameraRefComponent>(CameraRefComponent{ camera });

                std::println("Camera created!");
            });

    _world
        .system<
            ModelComponent,
            ModelAnimationComponent,
            const FileLoaderComponent>("MeshRendererInitialization")
        .kind(flecs::OnStart)
        .each([](
            const flecs::entity entity,
            ModelComponent &modelComponent,
            ModelAnimationComponent &modelAnimationComponent,
            const FileLoaderComponent &meshRendererComponent)
        {
            char path[1024];
            strcpy(path, GetWorkingDirectory());
            strcat(path, meshRendererComponent.Path);

            auto model = LoadModel(path);

            modelComponent.LoadedModel = model;
            
            int animationsCount = 0;
            auto animations = LoadModelAnimations(path, &animationsCount);

            modelAnimationComponent.AnimationsCount = animationsCount;
            modelAnimationComponent.Animations = animations;

            entity.remove<FileLoaderComponent>();
        });

    if (!_world.progress())
        throw std::runtime_error("Scene initialization failed!");
}

GameObject* Scene::NewGameObject(const char *name)
{
    const auto gameObject = new GameObject(name, &_world);
    _gameObjects.push_back(gameObject);
    return gameObject;
}

bool Scene::TryRemoveGameObject(const GameObject *gameObject)
{
    const auto foundItem = std::ranges::find(_gameObjects, gameObject);
    if (foundItem == _gameObjects.end())
        return false;

    _gameObjects.erase(foundItem);
    
    delete *foundItem.base();

    return true;
}

void Scene::Update(const float dt)
{
    _world
        .system<const CameraRefComponent>()
        .each([](const CameraRefComponent &cameraRef)
        {
            auto camera = const_cast<Camera*>(&cameraRef.CameraRef);
            UpdateCamera(camera, cameraRef.CameraRef.projection);
        });

    _world
        .system<
            const ModelComponent,
            const PositionComponent,
            const RotationEulerComponent,
            const ScaleComponent>()
        .each([](
            const ModelComponent &modelComponent,
            const PositionComponent &positionComponent,
            const RotationEulerComponent &rotationComponent,
            const ScaleComponent &scaleComponent)
        {
            DrawModelEx(
                modelComponent.LoadedModel,
                Vector3{positionComponent.X, positionComponent.Y, positionComponent.Z},
                Vector3{rotationComponent.X, rotationComponent.Y, rotationComponent.Z},
                0.f,
                Vector3{scaleComponent.X, scaleComponent.Y, scaleComponent.Z},
                WHITE);
        });

    if (!_world.progress(dt))
        throw std::runtime_error("Scene update failed!");
}

void Scene::Stop()
{
    _world
        .system<const ModelComponent>()
        .each([](const ModelComponent &modelComponent)
        {
           UnloadModel(modelComponent.LoadedModel);
        });

    if (!_world.progress())
        throw std::runtime_error("Scene stop failed!");
}
