#ifndef SAGARDOENGINE_ECS_ENTITY_H
#define SAGARDOENGINE_ECS_ENTITY_H

#include <string>

#include "flecs.h"

namespace SagardoEngine::Ecs
{
    class Entity final
    {
    private:
        const std::string _name;
        const flecs::world _world;
        const flecs::entity _entityId;
        
    public:
        Entity(
            const flecs::entity& entityId,
            const flecs::world& world,
            const std::string_view& name);
        ~Entity();

        void Destroy() const;
        
        template<typename T>
        void AddComponent(T component) const
        {
            _entityId.set<T>(component);
        }

        template<typename T>
        void RemoveComponent() const
        {
            auto entity = _entityId.remove<T>();
        }

        template<typename T>
        const T& GetComponent() const
        {
            return _entityId.get<T>();
        }
    };
}

#endif //SAGARDOENGINE_ECS_ENTITY_H
