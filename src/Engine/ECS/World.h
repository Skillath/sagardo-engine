#ifndef WORLD_H
#define WORLD_H

#include <string>

#include "Entity.h"
#include "ISystem.h"

namespace SagardoEngine::Ecs
{
    class World
    {
    private:
        flecs::world _world;
    
    public:
        ~World();
        [[nodiscard]]
        Entity CreateEntity(const std::string_view& name) const;
        static void DestroyEntity(const Entity& entity);

        void RunSystem(ISystem& system, float deltaTime);
        void Update(float deltaTime) const;
        
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
    };

}

#endif //WORLD_H
