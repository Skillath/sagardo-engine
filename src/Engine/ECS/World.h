#ifndef WORLD_H
#define WORLD_H

#include <string>

#include "Entity.h"
#include "ISystem.h"

namespace SagardoEngine::Ecs
{    
    class World final
    {
    private:
        flecs::world _world;
    
    public:
        ~World();
        
        [[nodiscard]]
        Entity CreateEntity(const std::string_view& name) const;
        static void DestroyEntity(const Entity& entity);

        World& RunSystem(ISystem& system, float deltaTime);
        
        flecs::world& GetInnerWorld() { return _world; }
        
        template<typename T>
        void AddComponent(T component) const
        {
            _world.set<T>(component);
        }

        template<typename T>
        void RemoveComponent() const
        {
            auto entity = _world.remove<T>();
        }

        template<typename T>
        const T& GetComponent() const
        {
            return _world.get<T>();
        }

        template<typename T>
        [[nodiscard]]
        Entity CreateArchetype(const std::string_view& name) const
        {
            const auto entity = _world
                .entity()
                .is_a<T>();

            return InitializeEntity(entity, _world, name);
        }

    private:
        static Entity InitializeEntity(
            const flecs::entity& entity,
            const flecs::world& world,
            const std::string_view& name);
    };

}

#endif //WORLD_H
