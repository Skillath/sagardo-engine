#ifndef SCENE_HPP
#define SCENE_HPP

#include "GameObject.hpp"
#include <flecs.h>
#include <vector>

#include "Components.hpp"
#include "IUpdatable.h"

namespace Engine 
{
    class Scene final : IStartable, IUpdatable, IStopable
    {     
        private:
            const char* _name;
            flecs::world _world;
            std::vector<GameObject*> _gameObjects;

        public:
            explicit Scene(const char* name);
            ~Scene() override;

            void Start() override;
            void Stop() override;
            void Update(float dt) override;

            void Render3D();
            GameObject* NewGameObject(const char* name);
            bool TryRemoveGameObject(const GameObject* gameObject);

    };
}

#endif