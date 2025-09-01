cmake_minimum_required(VERSION 3.26...3.31.6)

project(SagardoEngine VERSION 0.0.1 LANGUAGES C CXX)

# ---------- Options (must exist before add_subdirectory(deps)) ----------
option(SAGARDO_ENABLE_VK "Enable Vulkan backend (volk from deps)" OFF)
option(SAGARDO_WARN_AS_ERRORS "Treat warnings as errors" OFF)
option(SAGARDO_GL_DEBUG "Enable GL debug code paths" ON)

# ---------- Global ----------
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Static libs may be linked into shared/lib later (plugins), keep PIC on
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---------- Third-party ----------
add_subdirectory(deps) # exposes: flecs::flecs_static, glfw, glm, assimp, Jolt, stb_image, Freetype::Freetype, glad2, (optional) volk

# ---------- ECS static lib ----------
add_library(${PROJECT_NAME}.ecs STATIC
        src/Engine/ECS/World.cpp
        src/Engine/ECS/Entity.cpp
        src/Engine/ECS/Entity.h
        src/Engine/ECS/World.h
        src/Engine/ECS/ISystem.h
)
target_include_directories(${PROJECT_NAME}.ecs PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/ECS
)
target_link_libraries(${PROJECT_NAME}.ecs PUBLIC flecs::flecs_static)

# ---------- Core engine static lib ----------
add_library(${PROJECT_NAME} STATIC
        src/Engine/GameObject.cpp
        src/Engine/Scene.cpp
        src/Engine/Components.h
        src/Engine/IUpdatable.h
        src/Engine/IStartable.h
        src/Engine/IStopable.h
        src/Engine/IRenderPipeline.h
        src/Engine/ComponentUtils.cpp
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
        src/Engine/Mathf.h
        src/Engine/Color.h
        src/Engine/ColorUtils.h
        src/Engine/Mesh.cpp
        src/Engine/Mesh.h
        src/Engine/Model.cpp
        src/Engine/Model.h
        src/Engine/Logger.h
        src/Engine/Debug/OpenGlDebug.h
        src/Engine/Debug/OpenGlDebug.cpp
        src/Engine/Window.cpp
        src/Engine/Window.h
)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine
)

# Prevent GLFW from pulling GL headers; we control with glad/volk
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

if(SAGARDO_GL_DEBUG)
  target_compile_definitions(${PROJECT_NAME} PUBLIC SAGARDO_GL_DEBUG=1)
endif()

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        assimp
        Jolt
        stb_image
        PUBLIC
        glfw
        glm
        glad2
        ${PROJECT_NAME}.ecs
)

# Optional Vulkan backend (volk provided by deps when SAGARDO_ENABLE_VK=ON)
if(SAGARDO_ENABLE_VK)
  target_link_libraries(${PROJECT_NAME} PRIVATE volk)
  # volk target already defines VK_NO_PROTOTYPES / VOLK_STATIC_DEFINE
endif()

# ---------- Executable ----------
add_executable(DemoExecutable src/main.cpp)
target_link_libraries(DemoExecutable PRIVATE ${PROJECT_NAME})

# macOS: link frameworks on the final binary (window owner)
if(APPLE)
  target_link_libraries(DemoExecutable PRIVATE "-framework IOKit" "-framework Cocoa")
endif()

# ---------- Assets next to binary ----------
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/src/res
        $<TARGET_FILE_DIR:DemoExecutable>/res
        COMMENT "Smart-copying changed asset files to runtime dir"
)
add_dependencies(DemoExecutable copy_assets)

# ---------- Output directories (per-config) ----------
set(_bin_dir ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
foreach(_tgt IN ITEMS ${PROJECT_NAME} ${PROJECT_NAME}.ecs DemoExecutable)
  set_target_properties(${_tgt} PROPERTIES
          RUNTIME_OUTPUT_DIRECTORY                 "${_bin_dir}"
          RUNTIME_OUTPUT_DIRECTORY_DEBUG           "${_bin_dir}/debug"
          RUNTIME_OUTPUT_DIRECTORY_RELEASE         "${_bin_dir}/release"
          RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO  "${_bin_dir}/RelWithDebInfo"
          RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL      "${_bin_dir}/MinSizeRel"

          ARCHIVE_OUTPUT_DIRECTORY                 "${_bin_dir}"
          ARCHIVE_OUTPUT_DIRECTORY_DEBUG           "${_bin_dir}/debug"
          ARCHIVE_OUTPUT_DIRECTORY_RELEASE         "${_bin_dir}/release"
          ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO  "${_bin_dir}/RelWithDebInfo"
          ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL      "${_bin_dir}/MinSizeRel"

          LIBRARY_OUTPUT_DIRECTORY                 "${_bin_dir}"
          LIBRARY_OUTPUT_DIRECTORY_DEBUG           "${_bin_dir}/debug"
          LIBRARY_OUTPUT_DIRECTORY_RELEASE         "${_bin_dir}/release"
          LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO  "${_bin_dir}/RelWithDebInfo"
          LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL      "${_bin_dir}/MinSizeRel"
  )
endforeach()

# ---------- Warnings ----------
if(MSVC)
  foreach(_tgt IN ITEMS ${PROJECT_NAME} ${PROJECT_NAME}.ecs DemoExecutable)
    target_compile_options(${_tgt} PRIVATE /W4 /permissive-)
    if(SAGARDO_WARN_AS_ERRORS)
      target_compile_options(${_tgt} PRIVATE /WX)
    endif()
  endforeach()
else()
  foreach(_tgt IN ITEMS ${PROJECT_NAME} ${PROJECT_NAME}.ecs DemoExecutable)
    target_compile_options(${_tgt} PRIVATE -Wall -Wextra -Wpedantic)
    if(SAGARDO_WARN_AS_ERRORS)
      target_compile_options(${_tgt} PRIVATE -Werror)
    endif()
  endforeach()
endif()
