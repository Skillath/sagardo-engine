#ifndef SCENE_HPP
#define SCENE_HPP

#include <entt/entt.hpp>
#include <vector>

#include "GameObject.h"
#include "IStartable.h"
#include "IStopable.h"
#include "IUpdatable.h"

namespace SagardoEngine 
{
    class Scene final : public IStartable, public IUpdatable, public IStopable
    {     
        private:
            const char* _name;
            entt::registry _world;
            std::vector<GameObject*> _gameObjects;

        public:
            explicit Scene(const char* name);
            ~Scene() override;

            void Start() override;
            void Stop() override;
            void Update(float dt) override;
        
            GameObject* NewGameObject(const char* name);
            bool TryRemoveGameObject(const GameObject* gameObject);

    };
}

#endif