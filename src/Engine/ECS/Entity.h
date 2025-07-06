#ifndef ENTITY_H
#define ENTITY_H

#include <entt/entt.hpp>

namespace SagardoEngine::Ecs
{
    class Entity
    {
    private:
        entt::registry* _world;
        const entt::entity  _entityId;
        
    public:
        Entity(
            const entt::entity entityId,
            entt::registry* world);
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
