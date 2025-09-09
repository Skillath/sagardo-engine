# ECS as submodule (optional but recommended)
set(ENGINE_TARGET SagardoEngine)

add_library(${ENGINE_TARGET} STATIC
        src/GameObject.cpp
        src/Scene.cpp
        src/ComponentUtils.cpp
        src/RendererSystem.cpp
        src/RendererSystem.h
        src/ModelUnloaderSystem.cpp
        src/ModelUnloaderSystem.h
        src/RendererInitializerSystem.cpp
        src/RendererInitializerSystem.h
        src/Application.cpp
        src/Shader.cpp
        src/TimeProvider.cpp
        src/IO/File.cpp
        src/Physics/PhysicsEngineInitializerSystem.cpp
        src/Physics/PhysicsEngineInitializerSystem.h
        src/GlTextureLoader.cpp
        src/GlmUtils.cpp
        src/CameraUpdateSystem.cpp
        src/CameraUpdateSystem.h
        src/Mesh.cpp
        src/Model.cpp
        src/Debug/OpenGlDebug.cpp
        src/Window.cpp
        src/ECS/Entity.cpp
        src/ECS/World.cpp
        include/SagardoEngine/Components.h
        include/SagardoEngine/IUpdatable.h
        include/SagardoEngine/IStartable.h
        include/SagardoEngine/IStopable.h
        include/SagardoEngine/IRenderPipeline.h
        include/SagardoEngine/ComponentUtils.h
        include/SagardoEngine/Application.h
        include/SagardoEngine/Shader.h
        include/SagardoEngine/TimeProvider.h
        include/SagardoEngine/IO/File.h
        include/SagardoEngine/GlTextureLoader.h
        include/SagardoEngine/GlmUtils.h
        include/SagardoEngine/Mathf.h
        include/SagardoEngine/Color.h
        include/SagardoEngine/ColorUtils.h
        include/SagardoEngine/Mesh.h
        include/SagardoEngine/Model.h
        include/SagardoEngine/Debug/OpenGlDebug.h
        include/SagardoEngine/Logger.h
        include/SagardoEngine/Window.h
        include/SagardoEngine/ECS/Entity.h
        include/SagardoEngine/ECS/ISystem.h
        include/SagardoEngine/ECS/World.h
)
message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}")

# PUBLIC API include dir
target_include_directories(${ENGINE_TARGET}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(${ENGINE_TARGET} PUBLIC cxx_std_26)
target_compile_definitions(${ENGINE_TARGET} PRIVATE GLFW_INCLUDE_NONE)

# Link third-parties that you actually have now
target_link_libraries(${ENGINE_TARGET}
        PUBLIC
        ${ECS_TARGET}
        glad2
        PRIVATE
        stb_image
        flecs::flecs_static
)

set_target_properties(${ENGINE_TARGET} PROPERTIES FOLDER "Engine")


if(NOT GLAD_CUSTOM_OUTPUT)
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/bin/debug/")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/bin/release/")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/build/bin/MinSizeRel/")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/build/bin/RelWithDebInfo/")
else()
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${GLAD_CUSTOM_OUTPUT_DEBUG}")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${GLAD_CUSTOM_OUTPUT_RELEASE}")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${GLAD_CUSTOM_OUTPUT_MINSIZEREL}")
    set_target_properties(${ENGINE_TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${GLAD_CUSTOM_OUTPUT_RELWITHDEBINFO}")
endif()