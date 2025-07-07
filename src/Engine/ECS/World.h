#ifndef WORLD_H
#define WORLD_H

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
        Entity CreateEntity();
        static void DestroyEntity(const Entity& entity);

        void RunSystem(ISystem& system, float deltaTime);
        void Update(float deltaTime) const;
    };

}

#endif //WORLD_H
