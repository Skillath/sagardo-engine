#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <flecs.h>
#include <string>

namespace Engine
{
    class GameObject
    {
        private:
            flecs::world* _world;
            flecs::entity _entity;
            const char* _name;

        public:
            GameObject(const char *name, flecs::world *world);

            ~GameObject();

            template<typename T>
            void AddComponent(T component) const
            {
                _entity.set(component);
            }

            template<typename T>
            void RemoveComponent() const
            {
                auto entity = _entity.remove<T>();
                delete entity;
            }

            template<typename T>
            T GetComponent() const
            {
                return *_entity.get<T>();
            }
    };
}

#endif // !GAMEOBJECT_HPP
