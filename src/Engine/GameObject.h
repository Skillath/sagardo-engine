#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <flecs.h>
#include <string>

namespace SagardoEngine
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
                _entity.set<T>(component);
            }

            template<typename T>
            void RemoveComponent() const
            {
                auto entity = _entity.remove<T>();
            }

            template<typename T>
            T GetComponent() const
            {
                return *_entity.get<T>();
            }
    };
}

#endif // !GAMEOBJECT_HPP
