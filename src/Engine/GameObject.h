#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "ECS/Entity.h"
#include "ECS/World.h"

namespace SagardoEngine
{
    class GameObject
    {
        private:
            Ecs::World* _world;
            Ecs::Entity _entity;
        
            const char* _name;

        public:
            GameObject(
                const char* name, 
                Ecs::World* world);

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
