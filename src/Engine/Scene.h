#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <string>

#include "GameObject.h"
#include "IStartable.h"
#include "IStopable.h"
#include "IUpdatable.h"
#include "ECS/World.h"

namespace SagardoEngine 
{
    class Scene final :
        public IStartable,
        public IUpdatable,
        public IStopable
    {     
        private:
            const std::string _name;
        
            Ecs::World* _world;
            std::vector<GameObject*> _gameObjects;

        public:
            explicit Scene(const std::string_view& name);
            ~Scene() override;

            void Start() override;
            void Stop() override;
            void Update(float deltaTime) override;
        
            GameObject* NewGameObject(const char* name);
            bool TryRemoveGameObject(const GameObject* gameObject);
    };
}

#endif