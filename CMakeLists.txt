cmake_minimum_required(VERSION 3.26...3.31.6)
project(
        SagardoEngine 
        VERSION 0.0.1
        LANGUAGES C CXX)

include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 26)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json

find_package(OpenGL REQUIRED)
# Vulkan stuff
#find_package(Vulkan REQUIRED COMPONENTS glslc glslang SPIRV-Tools)

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
        ${SOURCES} ${HEADERS}
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
        src/Engine/Application.cpp
        src/Engine/Application.h
        src/Engine/Shader.cpp
        src/Engine/Shader.h
        src/Engine/TimeProvider.cpp
        src/Engine/TimeProvider.h
        src/Engine/IO/File.cpp
        src/Engine/IO/File.h
        src/Engine/Physics/PhysicsEngineInitializerSystem.cpp
        src/Engine/Physics/PhysicsEngineInitializerSystem.h
        src/Engine/GlTextureLoader.cpp
        src/Engine/GlTextureLoader.h
        src/Engine/GlmUtils.cpp
        src/Engine/GlmUtils.h
        src/Engine/CameraUpdateSystem.cpp
        src/Engine/CameraUpdateSystem.h
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        assimp
        glfw
        glm
        Jolt
        glad
        stb_image
        ${PROJECT_NAME}_ecs
)

# Executable
add_executable(DemoExecutable ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        src/ComponentUtils.cpp)

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

if(NOT GLAD_CUSTOM_OUTPUT)
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/bin/debug/")
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/bin/release/")
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/build/bin/MinSizeRel/")
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/build/bin/RelWithDebInfo/")
else()
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${GLAD_CUSTOM_OUTPUT_DEBUG}")
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${GLAD_CUSTOM_OUTPUT_RELEASE}")
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${GLAD_CUSTOM_OUTPUT_MINSIZEREL}")
  set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${GLAD_CUSTOM_OUTPUT_RELWITHDEBINFO}")
endif()

if (MSVC)
  target_compile_options(SagardoEngine PRIVATE /W4 /permissive-)
else()
  target_compile_options(SagardoEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()
