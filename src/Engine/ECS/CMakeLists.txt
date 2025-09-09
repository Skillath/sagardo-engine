set(ECS_TARGET SagardoEngine.Ecs)

add_library(${ECS_TARGET} STATIC
        src/World.cpp
        src/Entity.cpp
        include/SagardoEngine/ECS/Entity.h
        include/SagardoEngine/ECS/World.h
        include/SagardoEngine/ECS/ISystem.h
)

target_include_directories(${ECS_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${ECS_TARGET} PUBLIC flecs::flecs_static)
set_target_properties(${ECS_TARGET} PROPERTIES FOLDER "Engine/ECS")