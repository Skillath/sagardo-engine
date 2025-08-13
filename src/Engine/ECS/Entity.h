#ifndef ENTITY_H
#define ENTITY_H

#include "flecs.h"

namespace SagardoEngine::Ecs
{
    class Entity
    {
    private:
        flecs::world* _world;
        const flecs::entity  _entityId;
        
    public:
        Entity(
            const flecs::entity entityId,
            flecs::world* world);
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

#endif //ENTITY_H
