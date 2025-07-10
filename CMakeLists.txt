cmake_minimum_required(VERSION 3.26...3.31.6)
project(CiderEngine LANGUAGES C CXX)

include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 26)            # Requires C11 standard? Adjust if needed
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json

find_package(OpenGL REQUIRED)
add_subdirectory(deps)

# ECS Static Library
add_library(${PROJECT_NAME}_ecs STATIC
        src/Engine/ECS/World.cpp
        src/Engine/ECS/Entity.cpp
        src/Engine/ECS/Entity.h
        src/Engine/ECS/World.h
        src/Engine/ECS/ISystem.h
)

target_include_directories(${PROJECT_NAME}_ecs
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/ECS
)

target_link_libraries(${PROJECT_NAME}_ecs
        PUBLIC
        flecs::flecs_static        
)

# Core Engine Library
add_library(${PROJECT_NAME} STATIC
        src/Engine/GameObject.cpp
        src/Engine/Scene.cpp
        src/Engine/Components.h
        src/Engine/IUpdatable.h
        src/Engine/IStartable.h
        src/Engine/IStopable.h
        src/Engine/IRenderPipeline.h
        src/Engine/ComponentUtils.h
        src/Engine/RendererSystem.cpp
        src/Engine/RendererSystem.h
        src/Engine/ModelUnloaderSystem.cpp
        src/Engine/ModelUnloaderSystem.h
        src/Engine/RendererInitializerSystem.cpp
        src/Engine/RendererInitializerSystem.h
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        glad
        glfw
        glm
        assimp
        ${PROJECT_NAME}_ecs
)

# Executable
add_executable(DemoExecutable ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(DemoExecutable
        PRIVATE
        ${PROJECT_NAME}
)

# Copy assets
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/src/res
        ${CMAKE_CURRENT_BINARY_DIR}/src/res
        COMMENT "Smart-copying changed asset files"
)

add_dependencies(DemoExecutable copy_assets)

# macOS frameworks
if(APPLE)
  target_link_libraries(DemoExecutable
          PRIVATE
          "-framework IOKit"
          "-framework Cocoa"
          "-framework OpenGL"
  )
endif()
