#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

#include "ECS/Entity.h"
#include "ECS/World.h"

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

#endif // !GAMEOBJECT_HPP
