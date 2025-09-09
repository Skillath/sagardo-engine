#ifndef SAGARDOENGINE_GAMEOBJECT_HPP
#define SAGARDOENGINE_GAMEOBJECT_HPP

#include <string>
#include "../ECS/include/SagardoEngine/ECS/World.h"

namespace SagardoEngine
{
    class GameObject
    {
        private:
            const Ecs::World& _world;
            Ecs::Entity _entity;
        
            const std::string _name;

        public:
            GameObject(
                const std::string_view& name,
                const Ecs::World& world);

            ~GameObject();
        
        template<typename T>
        void AddComponent(T component) const
        {
            _entity.AddComponent<T>(component);
        }

        template<typename T>
        void RemoveComponent() const
        {
            _entity.RemoveComponent<T>();
        }

        template<typename T>
        T GetComponent() const
        {
            return _entity.GetComponent<T>();
        }
    };
}

#endif //SAGARDOENGINE_GAMEOBJECT_HPP
