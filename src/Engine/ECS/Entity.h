#ifndef ENTITY_H
#define ENTITY_H

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace SagardoEngine::Ecs
{
    class Entity
    {
    private:
        const char* _name;
        const entt::registry* _world;
        const entt::entity _entityId;
        
    public:
        Entity(
            const char* name,
            const entt::entity& entityId,
            const entt::registry* world);
        
        ~Entity();

        void Destroy() const;

        template<typename T>
        void AddComponent(T component) const
        {
            _world->emplace_or_replace<T>(_entityId, component);
        }

        template<typename T>
        void RemoveComponent() const
        {
            _world->remove<T>(_entityId);
        }

        template<typename T>
        T& GetComponent() const
        {
            return _world->get<T>(_entityId);
        }
    };
}


#endif //ENTITY_H
