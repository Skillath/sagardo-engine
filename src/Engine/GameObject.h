#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "ECS/Entity.h"
#include "ECS/World.h"

namespace SagardoEngine
{
    class GameObject
    {
        private:
            const Ecs::World _world;
            const Ecs::Entity _entity;
        
            const char* _name;

        public:
            GameObject(
                const char *name,
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
                auto entity = _entity.RemoveComponent<T>();
            }

            template<typename T>
            T GetComponent() const
            {
                return _entity.GetComponent<T>();
            }
    };
}

#endif // !GAMEOBJECT_HPP
